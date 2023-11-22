package org.example;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.WebDriver;

import java.util.List;

public class UploadTest {
    private static List<WebDriver> drivers;

    @BeforeAll
    public static void init() {
        Helpers.setupDrivers();
        drivers = Helpers.initDrivers();
    }

    @Test
    public void testUpload() {
        openSiteToUploading();
        signIn();
        clickUploadOnTheMainPage();
        clickUploadOnTheUploadPage();
        doUpload();
        changeInfo();
        finishCreating();
        waitForExplain();
    }

    @AfterAll
    public static void close() {
        Helpers.closeDrivers(drivers);
    }

    public void openSiteToUploading() {
        Helpers.openSite(drivers);
        Helpers.timeout();
    }

    public void signIn() {
        drivers.forEach(Helpers::signInToSite);
        Helpers.timeout();
    }

    public void clickUploadOnTheMainPage(){
        String xpath = "/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/a";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).click());
        Helpers.timeout();
    }

    public void clickUploadOnTheUploadPage(){
        String xpath = "/html/body/div/main/div/div[1]/center[2]/a";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).click());
        Helpers.timeout();
    }

    public void doUpload(){
        String xpath = "/html/body/div/main/div/div[1]/div[1]/div/div[2]/input";
        String script = "var inputs = document.getElementsByClassName('hidden');"
                + "for(var i = 0; i < inputs.length; i++) {"
                + "   inputs[i].style='display:block!important; visibility:visible!important; width:300px!important; height:50px!important;';"
                + "}";
        drivers.forEach(driver -> {
            if (driver instanceof JavascriptExecutor)
                ((JavascriptExecutor)driver).executeScript(script);
            else
                throw new IllegalStateException("This driver does not support JavaScript!");
            Helpers.findElement(driver, By.xpath(xpath)).sendKeys("E:\\bad_duck.jpg");
        });
        Helpers.timeout();
    }

    public void changeInfo(){
        String xpath = "/html/body/div/main/div/div[1]/div[2]/div[1]/div[3]/span[3]";
        String xpathDescription = "/html/body/div/main/div/div[1]/div[2]/div[1]/div[3]/div/div/div[2]/iframe";
        String xpath2 = "/html/body/div/main/div/div[1]/div[2]/div[1]/div[4]/span[2]";
        String xpathTags = "/html/body/div/main/div/div[1]/div[2]/div[1]/div[4]/input";
        String xpath3 = "/html/body/div/main/div/div[1]/div[2]/div[1]/div[8]/span[2]/span";
        String xpathSelect = "/html/body/div/main/div/div[1]/div[2]/div[1]/div[8]/span[2]/select";
        String xpathSelectItem = "/html/body/div/main/div/div[1]/div[2]/div[1]/div[8]/span[2]/select/option[2]";
        drivers.forEach(driver -> {
            Helpers.findElement(driver, By.xpath(xpath)).click();
            Helpers.findElement(driver, By.xpath(xpathDescription)).sendKeys("Test Description");
            Helpers.findElement(driver, By.xpath(xpath2)).click();
            Helpers.findElement(driver, By.xpath(xpathTags)).sendKeys("Test, Description, ITMO");
            Helpers.findElement(driver, By.xpath(xpath3)).click();
            Helpers.findElement(driver, By.xpath(xpathSelect)).click();
            Helpers.findElement(driver, By.xpath(xpathSelectItem)).click();
        });
        Helpers.timeout();
    }

    public void finishCreating(){
        String xpath = "/html/body/div/main/div/div[1]/button";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).click());
        Helpers.timeout();
    }

    public void waitForExplain() {
        Helpers.timeout(60000);
    }
}
