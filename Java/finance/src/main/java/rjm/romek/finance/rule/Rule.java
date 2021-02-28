package rjm.romek.finance.rule;

import lombok.RequiredArgsConstructor;

import java.util.Currency;
import java.util.Date;
import java.util.Map;

@RequiredArgsConstructor
public abstract class Rule {
    private final Currency targetValue;
    private final RuleType type;

    public abstract boolean applies(Map<Date, Currency> priceInTime);
}
