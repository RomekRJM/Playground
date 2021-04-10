package rjm.romek.finance.advisor;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import java.io.IOException;
import java.util.Date;
import java.util.SortedMap;
import javax.money.MonetaryAmount;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.EmailNotifier;
import rjm.romek.finance.notifier.NotificationBuilder;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@JsonDeserialize
public class Advisor {

  @JsonIgnore
  @Autowired
  private EmailNotifier notifier;

  private String recipient;
  private Grabber grabber;
  private String name;
  private Alert alert;
  private String cron;

  public void check() throws IOException, CouldNotGrabPriceException {
    validate();

    SortedMap<Date, MonetaryAmount> pricePoints = grabber.grabPrice();

    if (alert.checkTrigger(pricePoints)) {
      notifier.notify(recipient, new NotificationBuilder().build(name, alert, pricePoints));
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
