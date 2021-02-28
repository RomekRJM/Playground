package rjm.romek.finance.notifier;

import rjm.romek.finance.alert.Alert;

import java.util.Currency;
import java.util.Date;
import java.util.Map;

public interface Notifier {
    void notify(String who, Alert what, Map<Date, Currency> when);
}
