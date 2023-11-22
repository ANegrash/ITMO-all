package org.example;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.time.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class Helpers {
    private static final int millis = 300;

    public static void setupDrivers() {
        System.setProperty("webdriver.chrome.driver", System.getProperty("user.dir") + "/src/test/resources/drivers/chromedriver.exe");
        System.setProperty("webdriver.gecko.driver", System.getProperty("user.dir") + "/src/test/resources/drivers/geckodriver.exe");
    }

    public static List<WebDriver> initDrivers() {
        try (InputStream input = new FileInputStream("src/test/resources/settings.properties")) {
            Properties prop = new Properties();
            prop.load(input);
            String driverName = prop.getProperty("driverName");
            List<WebDriver> drivers = new ArrayList<>();

            if (driverName.equalsIgnoreCase("chrome")) {
                drivers.add(new ChromeDriver());
            } else if (driverName.equalsIgnoreCase("firefox")) {
                drivers.add(new FirefoxDriver());
            } else if (driverName.equalsIgnoreCase("all")) {
                drivers.add(new ChromeDriver());
                drivers.add(new FirefoxDriver());
            } else {
                throw new RuntimeException("Wrong driver name to setup");
            }

            return drivers;
        } catch (IOException ex) {
            throw new RuntimeException("No property for drivers setup");
        }
    }

    public static void closeDrivers(List<WebDriver> drivers) {
        drivers.forEach(WebDriver::close);
    }

    public static String getUsername() {
        try (InputStream input = new FileInputStream("src/test/resources/settings.properties")) {
            Properties prop = new Properties();
            prop.load(input);
            return prop.getProperty("username");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    public static String getPassword() {
        try (InputStream input = new FileInputStream("src/test/resources/settings.properties")) {
            Properties prop = new Properties();
            prop.load(input);
            return prop.getProperty("password");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    public static String getScreenName() {
        try (InputStream input = new FileInputStream("src/test/resources/settings.properties")) {
            Properties prop = new Properties();
            prop.load(input);
            return prop.getProperty("screen_name");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    public static void openSite(List<WebDriver> drivers) {
        drivers.forEach(driver ->
        {
            driver.manage().window().maximize();
            driver.get("https://archive.org/about/");
        });
    }

    public static void timeout() {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException ex) {
            System.out.println("Exception is caught");
        }
    }

    public static void timeout(int millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException ex) {
            System.out.println("Exception is caught");
        }
    }

    public static WebElement findElement(WebDriver driver, By by) {
        return new WebDriverWait(driver, Duration.ofSeconds(10)).until(ExpectedConditions.elementToBeClickable(by));
    }

    public static void signInToSite(WebDriver driver) {
        driver.findElement(By.xpath("/html/body/div/div[2]/ia-topnav/div[1]/primary-nav/nav/div[2]/login-button/div/span/a[2]")).click();
        driver.findElement(By.xpath("/html/body/div/main/div/div/div[2]/section[3]/form/label[1]/input")).sendKeys(getUsername());
        driver.findElement(By.xpath("/html/body/div/main/div/div/div[2]/section[3]/form/label[2]/div/input")).sendKeys(getPassword());
        driver.findElement(By.xpath("/html/body/div/main/div/div/div[2]/section[3]/form/input[3]")).click();
    }
}


