package rjm.romek.finance.scraper;

import org.jsoup.nodes.Element;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import javax.money.MonetaryAmount;
import java.io.IOException;
import java.util.Date;
import java.util.Map;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;

class GoogleGrabberTest {

  private GoogleGrabber googleGrabber;
  private final Element emptyElement = new Element("empty");

  @BeforeEach
  void setUp() {
    googleGrabber = new GoogleGrabber("google+share+price");
  }

  @Test
  public void shouldGrabPrice() throws IOException, CouldNotGrabPriceException {
    Map<Date, MonetaryAmount> dateMonetaryAmountMap = googleGrabber.grabPrice();
    Optional<MonetaryAmount> first = dateMonetaryAmountMap.values().stream().findFirst();

    assertEquals(1, dateMonetaryAmountMap.size());
    assertTrue(first.isPresent());
    assertEquals("USD", first.get().getCurrency().getCurrencyCode());
  }

  @Test
  public void shouldThrowExceptionOnWrongUrl() {
    googleGrabber = new GoogleGrabber("invalid");
    assertThrows(CouldNotGrabPriceException.class, googleGrabber::grabPrice);
  }

  @Test
  void shouldThrowExceptionWhenNoValue() {
    assertThrows(CouldNotGrabPriceException.class, () -> googleGrabber.getValue(emptyElement));
  }

  @Test
  void getUnit() {
    assertThrows(CouldNotGrabPriceException.class, () -> googleGrabber.getUnit(emptyElement));
  }
}