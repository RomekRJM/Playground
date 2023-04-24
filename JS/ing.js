let totalMortgage = 0;
let totalPaid = 0;
let standingBalance = 0;

function toNumber(currency) {
    return Number(currency.replace(' ', '').replace('PLN', '').replace(',', '.'));
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

const clickDropdown = async () => document.querySelector(".btn.dropdown-toggle.btn-default").click();
const pickYear = async year => document.querySelector("li[data-original-index='" + year + "'] a").click();

async function clickMoreIfExists() {
    let more = document.querySelector(".js-fetch-next-page.repayment-history-more_link");

    if (more) {
        more.click();
    }

    return more;
}

async function sumPaidExcludingBeginOfCreditLine() {
    let paid = 0;
    [...document.querySelectorAll('div.col-xs-8.col-sm-6.col-lg-8.one-line')]
        .filter(div => div.innerHTML.includes('Uruchomienie') || div.innerHTML.includes('Dodatkowe uruchomienie'))
        .forEach(div => div.parentElement.remove());

    document.querySelectorAll(".col-xs-4.col-sm-3.one-line.text-right strong")
        .forEach(e => paid += toNumber(e.innerText));

    return paid;
}

sleep(10)
    .then(() => document.querySelector('ing-icon[icon-id="ming:all:kredyt-gotowkowy"]').click())
    .then(() => sleep(2000))
    .then(() => document.querySelector('.product-item.product-bubble-custom div.js-bubble-region').click())
    .then(() => sleep(4000))
    .then(() => {
        totalMortgage = toNumber(document.querySelector('.budget-display_list-item_amount.amount.amount--med.col-lg-6.col-sm-7.col-xs-7.pa-0').innerText);
    })
    .then(() => {
        standingBalance = toNumber(document.querySelector('.budget-display_list-item_amount.amount.amount--big.col-lg-6.col-sm-7.col-xs-7.pa-0').innerText);
    })
    .then(() => document.querySelector('.js-repayment-history-button').click())
    .then(() => sleep(3000))
    .then(async () => {
            for (let year = 3; year < 20; year++) {
                await clickDropdown();
                await sleep(1000);
                await pickYear(year);
                await sleep(1000);

                while (await clickMoreIfExists()) {
                    await sleep(500);
                }

                let paidInYear = await sumPaidExcludingBeginOfCreditLine();

                if (paidInYear) {
                    totalPaid += paidInYear;
                } else {
                    break;
                }

            }
        }
    )
    .then(() => console.log('Zapłacono w sumie ' + (-1) * totalPaid + 'PLN. Do zapłaty ' + standingBalance + 'PLN z '
        + totalMortgage + 'PLN. Koszt kredytu: ' + (-1 * (totalMortgage + totalPaid - standingBalance)) + 'PLN.' ));
