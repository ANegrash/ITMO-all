package org.example;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;

import java.util.List;

public class SearchTest {
    private static List<WebDriver> drivers;
    private static final String request = "itmo";

    @BeforeAll
    public static void init() {
        Helpers.setupDrivers();
        drivers = Helpers.initDrivers();
    }

    @Test
    public void testSearching() {
        openSiteToSearching();
        enterInSearchLine();
        clickSearchButton();
    }

    @AfterAll
    public static void close() {
        Helpers.closeDrivers(drivers);
    }

    public void openSiteToSearching() {
        Helpers.openSite(drivers);
        Helpers.timeout();
    }

    public void enterInSearchLine() {
        String searchLineXpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/nav-search/div/form/input";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(searchLineXpath)).sendKeys(request));
        Helpers.timeout();
    }

    public void clickSearchButton() {
        String expectedURL = "https://archive.org/search?query=itmo";
        String xpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/nav-search/div/form/button";
        drivers.forEach(driver -> {
            Helpers.findElement(driver, By.xpath(xpath)).click();
            String redirectURL = driver.getCurrentUrl();
            Assertions.assertEquals(expectedURL, redirectURL);
        });
        Helpers.timeout();
    }
}
