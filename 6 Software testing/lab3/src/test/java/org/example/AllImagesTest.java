package org.example;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;

import java.util.List;

public class AllImagesTest {
    private static List<WebDriver> drivers;

    @BeforeAll
    public static void init() {
        Helpers.setupDrivers();
        drivers = Helpers.initDrivers();
    }

    @Test
    public void testAllImagesView() {
        openSite();
        goToAllImagesPage();
        checkSectionName();
    }

    @AfterAll
    public static void close() {
        Helpers.closeDrivers(drivers);
    }

    public void openSite() {
        Helpers.openSite(drivers);
        Helpers.timeout();
    }

    public void goToAllImagesPage(){
        String xpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/media-menu/div/div/nav/div/media-button[6]/a";
        String xpathItem = "/html/body/div/div[2]/ia-topnav/div[1]/media-slider/div/div/div/div/media-subnav[2]/div[2]/ul/li[1]/a";
        drivers.forEach(driver -> {
            Helpers.findElement(driver, By.xpath(xpath)).click();
            Helpers.findElement(driver, By.xpath(xpathItem)).click();
        });
        Helpers.timeout();
    }

    public void checkSectionName() {
        String xpath = "/html/body/div/main/div[2]/div/div[1]/div[1]/div/div[1]/div[2]/h1";
        drivers.forEach(driver -> {
            String nameAtSite = Helpers.findElement(driver, By.xpath(xpath)).getText();
            Assertions.assertEquals("Image", nameAtSite);
        });
        Helpers.timeout();
    }
}
