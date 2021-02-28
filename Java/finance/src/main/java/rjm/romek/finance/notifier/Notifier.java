package rjm.romek.finance.notifier;

import rjm.romek.finance.rule.Rule;

import java.util.Currency;
import java.util.Date;

public interface Notifier {
    void notify(String who, Currency price, Date atTimestamp, Rule rule);
}
