package rjm.romek.finance.rule;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryDateUtil;

class PriceBelowRuleTest {

  private final PriceBelowRule priceBelowRule = new PriceBelowRule(MonetaryDateUtil.getDollars(1));

  @Test
  public void shouldApply() {
    assertTrue(priceBelowRule.applies(MonetaryDateUtil.getDollars(0.5).getMonetaryAmount()));
  }

  @Test
  public void shouldNotApply() {
    assertFalse(priceBelowRule.applies(MonetaryDateUtil.getDollars(2).getMonetaryAmount()));
  }
}