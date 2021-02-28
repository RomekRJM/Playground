package rjm.romek.finance.scraper;

import lombok.AllArgsConstructor;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import javax.money.Monetary;
import javax.money.MonetaryAmount;
import java.io.IOException;
import java.util.Date;
import java.util.List;
import java.util.Map;

@AllArgsConstructor
public class GoogleGrabber implements Grabber {
    private static final String SEARCH_URL = "https://www.google.com/search?q=%s&ie=utf-8&oe=utf-8";
    private static final String QUERY_SEARCH_EXPRESSION = "g-card-section div g-card-section div span span span";

    private final String asset;

    @Override
    public Map<Date, MonetaryAmount> grabPrice() throws IOException {
        String assetSearchUrl = String.format(SEARCH_URL, asset);

        Document doc = Jsoup.connect(assetSearchUrl).get();
        Elements elements = doc.select(QUERY_SEARCH_EXPRESSION);

        List<Element> found = elements.subList(0, 2);
        Double value = Double.valueOf(found.get(0).childNodes().get(0).toString().replaceAll(",", ""));
        String currency = found.get(1).childNodes().get(0).toString().trim();

        return Map.of(
                new Date(),
                Monetary.getDefaultAmountFactory()
                        .setCurrency(Monetary.getCurrency(currency))
                        .setNumber(value)
                        .create()
        );
    }
}
