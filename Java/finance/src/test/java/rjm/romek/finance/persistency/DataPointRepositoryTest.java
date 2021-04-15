package rjm.romek.finance.persistency;

import static java.util.concurrent.TimeUnit.SECONDS;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
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

  private void generateLargeDataSet() {
    for (int i = 0; i < 1000; ++i) {
      List<DataPoint> dataPoints = new ArrayList<>();
      Date date = new Date();
      for (int j = 0; j < 100; ++j) {
        dataPoints.add(
            DataPoint.builder().date(date).value(j).advisorName(ADVISOR).currencyCode(CURRENCY)
                .build()
        );
      }
      repository.saveAll(dataPoints);
    }
  }
}