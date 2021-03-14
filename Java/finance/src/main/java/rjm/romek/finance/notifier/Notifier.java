package rjm.romek.finance.notifier;

import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import rjm.romek.finance.alert.Alert;

import javax.money.MonetaryAmount;
import java.util.Date;
import java.util.Map;

@JsonDeserialize(as = EmailNotifier.class)
public interface Notifier {

  void notify(String who, Alert what, Map<Date, MonetaryAmount> when);
}
