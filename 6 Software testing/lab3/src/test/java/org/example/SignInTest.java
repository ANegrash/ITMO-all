package org.example;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;

import java.util.List;

public class SignInTest  {
    private static List<WebDriver> drivers;
    private final String username = Helpers.getUsername();
    private final String password = Helpers.getPassword();
    private final String screen_name = Helpers.getScreenName();

    @BeforeAll
    public static void init() {
        Helpers.setupDrivers();
        drivers = Helpers.initDrivers();
    }

    @Test
    public void testSignIn() {
        openSiteToSignIn();
        clickSignInOnTheMainPage();
        enterUsername();
        enterPassword();
        clickSignInButton();
        checkUsernameInProfile();
    }

    @AfterAll
    public static void close() {
        Helpers.closeDrivers(drivers);
    }

    public void openSiteToSignIn() {
        Helpers.openSite(drivers);
        Helpers.timeout();
    }

    public void clickSignInOnTheMainPage(){
        String xpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/div[2]/login-button/div/span/a[2]";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).click());
        Helpers.timeout();
    }

    public void enterUsername() {
        String xpath = "/html/body/div/main/div/div/div[2]/section[3]/form/label[1]/input";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).sendKeys(username));
        Helpers.timeout();
    }

    public void enterPassword() {
        String xpath = "/html/body/div/main/div/div/div[2]/section[3]/form/label[2]/div/input";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).sendKeys(password));
        Helpers.timeout();
    }

    public void clickSignInButton() {
        String xpath = "/html/body/div/main/div/div/div[2]/section[3]/form/input[3]";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).click());
        Helpers.timeout();
    }

    public void checkUsernameInProfile() {
        String xpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/div[2]/button/span";
        drivers.forEach(driver -> {
            String actualScreenName = Helpers.findElement(driver, By.xpath(xpath)).getText();
            Assertions.assertEquals(screen_name, actualScreenName);
        });
        Helpers.timeout();
    }
}
