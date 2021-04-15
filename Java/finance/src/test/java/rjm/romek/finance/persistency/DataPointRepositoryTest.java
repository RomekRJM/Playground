package rjm.romek.finance.persistency;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class DataPointRepositoryTest {

  @Autowired
  private DataPointRepository repository;

  private static final String ADVISOR = "abcd";
  private static final String CURRENCY = "usd";

  @Test
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
        DataPoint dp = new DataPoint();
        dp.setDate(date);
        dp.setValue(j);
        dp.setAdvisorName(ADVISOR);
        dp.setCurrencyCode(CURRENCY);
      }
      repository.saveAll(dataPoints);
    }
  }
}