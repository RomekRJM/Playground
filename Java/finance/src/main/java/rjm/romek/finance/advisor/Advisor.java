package rjm.romek.finance.advisor;

import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Map.Entry;
import java.util.SortedMap;
import javax.money.MonetaryAmount;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.springframework.transaction.annotation.Transactional;
import rjm.romek.finance.SpringContext;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.EmailNotifier;
import rjm.romek.finance.notifier.NotificationBuilder;
import rjm.romek.finance.persistency.DataPoint;
import rjm.romek.finance.persistency.DataPointRepository;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@JsonDeserialize
public class Advisor {

  private String recipient;
  private Grabber grabber;
  private String name;
  private Alert alert;
  private String cron;

  public void check() throws IOException, CouldNotGrabPriceException {
    validate();

    saveDataPoints(grabber.grabPrice());
    List<DataPoint> pricePoints = getDataPointRepository()
        .findTop32DataPointsByAdvisorNameOrderByDateDesc(name);

    if (alert.checkTrigger(pricePoints)) {
      getNotifier().notify(
          recipient,
          new NotificationBuilder().build(name, alert, pricePoints)
      );
    }
  }

  private EmailNotifier getNotifier() {
    return SpringContext.getBean(EmailNotifier.class);
  }

  private DataPointRepository getDataPointRepository() {
    return SpringContext.getBean(DataPointRepository.class);
  }

  @Transactional
  void saveDataPoints(SortedMap<Date, MonetaryAmount> pricePoints) {
    List<DataPoint> dataPoints = new ArrayList<>();
    for (Entry<Date, MonetaryAmount> entry : pricePoints.entrySet()) {
      MonetaryAmount monetaryAmount = entry.getValue();
      Date date = entry.getKey();
      dataPoints
          .add(DataPoint.builder().date(date).value(monetaryAmount.getNumber().doubleValue())
              .advisorName(name).currencyCode(monetaryAmount.getCurrency().getCurrencyCode())
              .build());
    }
    getDataPointRepository().saveAll(dataPoints);
  }

  private void validate() {
    assert grabber != null;
    assert name != null;
    assert alert != null;
    assert cron != null;
  }
}
