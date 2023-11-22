package org.example;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;

import java.util.List;

public class BlogTest {
    private static List<WebDriver> drivers;

    @BeforeAll
    public static void init() {
        Helpers.setupDrivers();
        drivers = Helpers.initDrivers();
    }

    @Test
    public void testOpenBlogRecentArticle() {
        openSite();
        goToBlogPage();
        clickRecentArticleTitle();
        checkPostIsLast();
    }

    @AfterAll
    public static void close() {
        Helpers.closeDrivers(drivers);
    }

    public void openSite() {
        Helpers.openSite(drivers);
        Helpers.timeout();
    }

    public void goToBlogPage(){
        String xpath = "/html/body/div/div[2]/ia-topnav/desktop-subnav/ul/li[2]/a";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).click());
        Helpers.timeout();
    }

    public void clickRecentArticleTitle() {
        String xpath = "/html/body/div/div/div[2]/aside[2]/ul/li[1]/a";
        drivers.forEach(driver -> Helpers.findElement(driver, By.xpath(xpath)).click());
        Helpers.timeout();
    }

    public void checkPostIsLast() {
        String xpath = "/html/body/div/div/div[1]/div/article/header/div/a/time";
        drivers.forEach(driver -> {
            String currentDate = Helpers.findElement(driver, By.xpath(xpath)).getText();
            Assertions.assertEquals("May 20, 2023", currentDate);
        });
        Helpers.timeout();
    }
}
