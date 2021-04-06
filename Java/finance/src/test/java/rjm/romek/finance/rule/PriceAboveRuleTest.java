package rjm.romek.finance.rule;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryDateUtil;

class PriceAboveRuleTest {

  private final PriceAboveRule priceAboveRule = new PriceAboveRule(MonetaryDateUtil.getDollars(1));

  @Test
  public void shouldApply() {
    assertTrue(priceAboveRule.applies(MonetaryDateUtil.getDollars(2).getMonetaryAmount()));
  }

  @Test
  public void shouldNotApply() {
    assertFalse(priceAboveRule.applies(MonetaryDateUtil.getDollars(0.5).getMonetaryAmount()));
  }
}