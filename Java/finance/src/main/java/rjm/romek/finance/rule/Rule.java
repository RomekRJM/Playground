package rjm.romek.finance.rule;

import com.fasterxml.jackson.annotation.JsonSubTypes;
import com.fasterxml.jackson.annotation.JsonSubTypes.Type;
import com.fasterxml.jackson.annotation.JsonTypeInfo;
import com.fasterxml.jackson.annotation.JsonTypeInfo.Id;
import javax.money.MonetaryAmount;
import lombok.Getter;
import lombok.RequiredArgsConstructor;
import rjm.romek.finance.monetary.SimpleMonetaryAmount;

@Getter
@RequiredArgsConstructor
@JsonTypeInfo(use = Id.NAME, property = "type")
@JsonSubTypes({
    @Type(value = PriceAboveRule.class, name = "PriceAboveRule")
})
public abstract class Rule {

  protected final SimpleMonetaryAmount targetValue;
  protected final RuleType type;

  public Rule() {
    this.targetValue = null;
    this.type = null;
  }

  public abstract boolean applies(MonetaryAmount value);
}
