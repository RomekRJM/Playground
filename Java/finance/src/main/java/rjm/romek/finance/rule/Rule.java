package rjm.romek.finance.rule;

import lombok.RequiredArgsConstructor;

import javax.money.MonetaryAmount;
import java.util.Date;

@RequiredArgsConstructor
public abstract class Rule {
    private final MonetaryAmount targetValue;
    private final RuleType type;

    public abstract boolean applies(Date date, MonetaryAmount price);
}
