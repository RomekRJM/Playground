import lombok.AllArgsConstructor;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;
import rjm.romek.finance.notifier.Notifier;

import javax.money.MonetaryAmount;
import java.io.IOException;
import java.util.Date;
import java.util.Map;
import java.util.stream.Collectors;

@AllArgsConstructor
public class Advisor {

  private Notifier notifier;

  public void check(Grabber grabber, Alert alert) throws IOException, CouldNotGrabPriceException {
    Map<Date, MonetaryAmount> pricePoints = grabber.grabPrice();

    Map<Date, MonetaryAmount> dataPointsWhenTriggered =
        pricePoints.entrySet().stream()
            .filter(entry -> alert.isTriggered(entry.getKey(), entry.getValue()))
            .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));

    if (dataPointsWhenTriggered.isEmpty()) {
      return;
    }

    notifier.notify("romek@example.com", alert, dataPointsWhenTriggered);
  }
}
