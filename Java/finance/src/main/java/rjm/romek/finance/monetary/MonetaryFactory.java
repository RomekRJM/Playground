package rjm.romek.finance.monetary;

import java.util.Map;
import lombok.SneakyThrows;

public class MonetaryFactory {

  private final Map<String, Class<? extends MonetaryConverter>> converters = Map.of(
      "GBX", GBXConverter.class
  );

  @SneakyThrows // instantiation errors won't happen here
  public MonetaryConverter create(String currencyCode) {
    if (converters.containsKey(currencyCode)) {
      return converters.get(currencyCode).getDeclaredConstructor().newInstance();
    }

    return new DefaultConverter();
  }
}
