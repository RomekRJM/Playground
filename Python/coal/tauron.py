import time
import os

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium_stealth import stealth
from time import sleep


def create_stealth_webdriver():
        chrome_options = Options()
        # chrome_options.add_argument("--disable-extensions")
        # chrome_options.add_argument("--disable-gpu")
        # chrome_options.add_argument("--headless")
        chrome_options.add_argument("--user-agent=Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) "
                                    "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.64 Safari/537.36")
        chrome_options.add_argument('--disable-extensions')
        chrome_options.add_argument('--profile-directory=Default')
        chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
        chrome_options.add_experimental_option('useAutomationExtension', False)
        # chrome_options.add_argument("--incognito")
        chrome_options.add_argument("--disable-plugins-discovery")
        chrome_options.add_argument("--enable-javascript")

        driver = webdriver.Chrome('/Users/roman.subik/Downloads/chromedriver', options=chrome_options)
        stealth(driver,
                languages=["en-US", "en"],
                vendor="Google Inc.",
                platform="Win32",
                webgl_vendor="Intel Inc.",
                renderer="Intel Iris OpenGL Engine",
                fix_hairline=True,
                )

        return driver


def buy_webarchive(driver):
        start_url = "https://web.archive.org/web/20210513093544/https://sklep.tauron.pl/"
        driver.get(start_url)
        # print(driver.page_source.encode("utf-8"))
        driver.find_element(By.CLASS_NAME, 'wybieram').click()
        sleep(5)
        driver.execute_script(f"document.getElementById('postal-code-input').focus();")
        postal = driver.find_element(By.NAME, 'zip_code_id')
        postal.click()
        postal.send_keys("31542")


def login_tauron(driver):
        # login-btn-top
        start_url = "https://sklep.tauron.pl/"
        driver.get(start_url)
        # print(driver.page_source.encode("utf-8"))
        driver.execute_script(f"document.getElementById('span.visible-xs-inline')[0].click();")
        sleep(5)
        driver.find_element(By.NAME, 'username').send_keys(os.getenv('USER'))
        driver.find_element(By.NAME, 'password').send_keys(os.getenv('PASS'))
        driver.find_element(By.XPATH, 'input[type="submit"]').click()


driver = create_stealth_webdriver()
# buy_webarchive(driver)
login_tauron(driver)
# driver.quit()
