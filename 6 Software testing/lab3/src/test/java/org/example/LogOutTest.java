package org.example;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;

import java.util.List;

public class LogOutTest {
    private static List<WebDriver> drivers;

    @BeforeAll
    public static void init() {
        Helpers.setupDrivers();
        drivers = Helpers.initDrivers();
    }

    @Test
    public void testLogOut() {
        openSite();
        signIn();
        tryLogOut();
        checkSignInButton();
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

    public void tryLogOut(){
        String xpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/div[2]/button";
        String xpathItem = "/html/body/div/div[2]/ia-topnav/user-menu/div/nav/ul/li[8]/a";
        drivers.forEach(driver -> {
            Helpers.findElement(driver, By.xpath(xpath)).click();
            Helpers.findElement(driver, By.xpath(xpathItem)).click();
        });
        Helpers.timeout();
    }

    public void checkSignInButton() {
        String xpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/div[2]/login-button/div/span/a[2]";
        drivers.forEach(driver -> {
            String logInButton = Helpers.findElement(driver, By.xpath(xpath)).getText();
            Assertions.assertEquals("LOG IN", logInButton);
        });
        Helpers.timeout();
    }
}
