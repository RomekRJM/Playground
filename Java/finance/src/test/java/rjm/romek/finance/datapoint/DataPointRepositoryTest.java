package rjm.romek.finance.datapoint;

import static java.util.concurrent.TimeUnit.SECONDS;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import rjm.romek.finance.datapoint.model.DataPoint;
import rjm.romek.finance.datapoint.model.DataPointRepository;

@SpringBootTest
@ActiveProfiles(profiles = "test")
class DataPointRepositoryTest {

  @Autowired
  private DataPointRepository repository;

  private static final String ADVISOR = "abcd";
  private static final String CURRENCY = "usd";

  @Test
  @Timeout(value = 10, unit = SECONDS)
  public void loadTest() {
    generateLargeDataSet();

    List<DataPoint> dataPoints = repository
        .findTop32DataPointsByAdvisorNameOrderByDateDesc(ADVISOR);

    assertEquals(32, dataPoints.size());
  }

  @AfterEach
  public void cleanUp() {
    repository.deleteAll();
    repository.flush();
  }

  private void generateLargeDataSet() {
    for (int i = 0; i < 1000; ++i) {
      List<DataPoint> dataPoints = new ArrayList<>();
      Date date = new Date();
      for (int j = 0; j < 100; ++j) {
        dataPoints.add(
            DataPoint.builder().date(date).value((double) j).advisorName(ADVISOR)
                .currencyCode(CURRENCY)
                .build()
        );
      }
      repository.saveAll(dataPoints);
    }
  }
}