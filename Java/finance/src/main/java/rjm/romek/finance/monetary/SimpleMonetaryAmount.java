package rjm.romek.finance.monetary;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import javax.money.Monetary;
import javax.money.MonetaryAmount;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Getter
@NoArgsConstructor
@JsonDeserialize
public class SimpleMonetaryAmount {
  private String currencyCode;
  private Number amount;

  public SimpleMonetaryAmount(MonetaryAmount monetaryAmount) {
    this.currencyCode = monetaryAmount.getCurrency().getCurrencyCode();
    this.amount = monetaryAmount.getNumber();
  }

  @JsonIgnore
  public MonetaryAmount getMonetaryUnit() {
    return Monetary.getDefaultAmountFactory()
        .setCurrency(Monetary.getCurrency(currencyCode))
        .setNumber(amount)
        .create();
  }
}
