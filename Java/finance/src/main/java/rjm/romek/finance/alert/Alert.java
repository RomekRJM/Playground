package rjm.romek.finance.alert;

import lombok.Getter;
import lombok.RequiredArgsConstructor;
import rjm.romek.finance.rule.Rule;

import java.util.Currency;
import java.util.Date;

@Getter
@RequiredArgsConstructor
public abstract class Alert {
    private final Currency target;
    private final Rule rule;

    public abstract boolean isTriggered(Date atTimestamp, Currency value);
}
