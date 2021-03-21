package rjm.romek.finance.rule;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryUtil;

class PriceBelowRuleTest {

  private final PriceBelowRule priceBelowRule = new PriceBelowRule(MonetaryUtil.getDollars(1));

  @Test
  public void shouldApply() {
    assertTrue(priceBelowRule.applies(MonetaryUtil.getDollars(0.5).getMonetaryUnit()));
  }

  @Test
  public void shouldNotApply() {
    assertFalse(priceBelowRule.applies(MonetaryUtil.getDollars(2).getMonetaryUnit()));
  }
}