package rjm.romek.finance.rule;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryUtil;

class PriceAboveRuleTest {

  private final PriceAboveRule priceAboveRule = new PriceAboveRule(MonetaryUtil.getDollars(1));

  @Test
  public void shouldApply() {
    assertTrue(priceAboveRule.applies(MonetaryUtil.getDollars(2).getMonetaryAmount()));
  }

  @Test
  public void shouldNotApply() {
    assertFalse(priceAboveRule.applies(MonetaryUtil.getDollars(0.5).getMonetaryAmount()));
  }
}