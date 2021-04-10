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
    @Type(value = PriceAboveRule.class, name = "PriceAboveRule"),
    @Type(value = PriceAboveRule.class, name = "PriceBelowRule")
})
public abstract class Rule {

  protected final SimpleMonetaryAmount targetValue;

  public Rule() {
    this.targetValue = null;
  }

  public abstract boolean applies(MonetaryAmount value);
}
