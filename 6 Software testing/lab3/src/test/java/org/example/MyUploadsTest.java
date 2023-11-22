package org.example;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;

import java.util.List;

public class MyUploadsTest {
    private static List<WebDriver> drivers;
    private final String display_name = Helpers.getPassword();

    @BeforeAll
    public static void init() {
        Helpers.setupDrivers();
        drivers = Helpers.initDrivers();
    }

    @Test
    public void testMyUploads() {
        openSite();
        signIn();
        goToMyUploadsPage();
        checkMyName();
    }

    @AfterAll
    public static void close() {
        Helpers.closeDrivers(drivers);
    }

    public void openSite() {
        Helpers.openSite(drivers);
        Helpers.timeout();
    }

    public void signIn() {
        drivers.forEach(Helpers::signInToSite);
        Helpers.timeout();
    }

    public void goToMyUploadsPage(){
        String xpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/div[2]/button";
        String xpathItem = "/html/body/div/div[2]/ia-topnav/user-menu/div/nav/ul/li[2]/a";
        drivers.forEach(driver -> {
            Helpers.findElement(driver, By.xpath(xpath)).click();
            Helpers.findElement(driver, By.xpath(xpathItem)).click();
        });
        Helpers.timeout();
    }

    public void checkMyName() {
        String xpath = "/html/body/div/main/div[2]/div/div[1]/div[4]/h1";
        drivers.forEach(driver -> {
            String nameAtSite = Helpers.findElement(driver, By.xpath(xpath)).getText();
            Assertions.assertEquals(display_name, nameAtSite);
        });
        Helpers.timeout();
    }
}
