function get_item_count(title) {
    var title_text = title.innerText.toLowerCase();
    var math_expression = title_text.match(/[0-9]+\s*x\s*[0-9]+/g, "");

    if (math_expression) {
        return parseInt(eval(math_expression[0].replace("x", "*")))
    }

    title_text = title_text.replace(/[^0-9][0-9]\s+/g, "");
    title_text = title_text.replace(/[0-9]+\s+-\s+[0-9]+/g, "");
    var item_count = title_text.match(/[0-9]+/);

    if (item_count) {
        return parseInt(item_count[0]);
    }

    return 1;
}

function get_price(price) {
    var price_text = price.innerText;
    price_text = price_text.replace(",", ".");
    price_text = price_text.replace("zł", "");
    price_text = price_text.replace(" ", "");

    return parseFloat(price_text);
}

titles = $$('article div div div h2')
            .filter(el => el.innerText.trim().length > 0)
prices = $$('article div div div span')
            .filter(el => el.innerText.match(/[0-9]+,[0-9]+ zł$/g))
            .filter(el => el.classList.length == 2);

var i;
var bestBang4Buck = 9999999;
var bestItem = '';
var bestCount = 0;

for (i = 0; i < titles.length; i++) {
    var title_element = titles[i];
    var price_element = prices[i];

    var price = get_price(price_element);
    var item_count = get_item_count(title_element);
    var ratio = price / item_count;

    if (ratio < bestBang4Buck) {
        bestBang4Buck = ratio;
        bestItem = title_element;
        bestCount = item_count;
        console.log(price + "/" + item_count + "=" + ratio);
    }
}

console.log("Best item is " + bestItem.innerText + " at price point "
        + bestBang4Buck + " PLN/item. Total quantity: " + bestCount);

bestItem;
