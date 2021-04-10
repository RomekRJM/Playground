package rjm.romek.finance.advisor;

import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import java.io.IOException;
import java.util.Date;
import java.util.SortedMap;
import javax.money.MonetaryAmount;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.EmailNotifier;
import rjm.romek.finance.notifier.MessageBuilder;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@JsonDeserialize
public class Advisor {

  private EmailNotifier notifier;
  private Grabber grabber;
  private String name;
  private Alert alert;
  private String cron;

  public void check() throws IOException, CouldNotGrabPriceException {
    validate();

    SortedMap<Date, MonetaryAmount> pricePoints = grabber.grabPrice();

    if (alert.checkTrigger(pricePoints)) {
      notifier.notify(new MessageBuilder().build(alert, pricePoints));
    }
  }

  private void validate() {
    assert notifier != null;
    assert grabber != null;
    assert name != null;
    assert alert != null;
    assert cron != null;
  }
}
