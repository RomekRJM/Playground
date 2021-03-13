import java.io.IOException;
import java.util.Date;
import java.util.Map;
import javax.money.MonetaryAmount;
import lombok.AllArgsConstructor;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.Notifier;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

@AllArgsConstructor
public class Advisor {

  private Notifier notifier;

  public void check(Grabber grabber, Alert alert) throws IOException, CouldNotGrabPriceException {
    Map<Date, MonetaryAmount> pricePoints = grabber.grabPrice();

    if (alert.checkTrigger(pricePoints)) {
      return;
    }

    notifier.notify("romek@example.com", alert, pricePoints);
  }
}
