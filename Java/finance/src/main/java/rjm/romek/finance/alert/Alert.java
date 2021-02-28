package rjm.romek.finance.alert;

import rjm.romek.finance.rule.Rule;

import java.util.Currency;
import java.util.Date;

public interface Alert {
    boolean isTriggered(Currency price, Date atTimestamp, Rule rule);
}
