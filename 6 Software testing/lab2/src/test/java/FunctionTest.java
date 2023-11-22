import org.apache.commons.csv.CSVFormat;
import org.apache.commons.csv.CSVRecord;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;
import org.junit.jupiter.params.provider.ValueSource;
import org.mockito.Mockito;

import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;

class FunctionTest {
    static double functionEps = 0.1;
    double eps = 0.1;

    static Sec secMock;
    static Cos cosMock;
    static Sin sinMock;
    static Ln lnMock;
    static Log logMock;
    static Cot cotMock;
    static Csc cscMock;
    static Tan tanMock;

    static Reader secIn;
    static Reader cosIn;
    static Reader sinIn;
    static Reader lnIn;
    static Reader log2In;
    static Reader log3In;
    static Reader log5In;
    static Reader log10In;
    static Reader cotIn;
    static Reader cscIn;
    static Reader tanIn;

    @BeforeAll
    static void init() {
        secMock = Mockito.mock(Sec.class);
        cosMock = Mockito.mock(Cos.class);
        sinMock = Mockito.mock(Sin.class);
        lnMock = Mockito.mock(Ln.class);
        logMock = Mockito.mock(Log.class);
        cotMock = Mockito.mock(Cot.class);
        cscMock = Mockito.mock(Csc.class);
        tanMock = Mockito.mock(Tan.class);
        try {
            secIn = new FileReader("src/lab2/resources/CsvFiles/Inputs/SecIn.csv");
            cosIn = new FileReader("src/lab2/resources/CsvFiles/Inputs/CosIn.csv");
            sinIn = new FileReader("src/lab2/resources/CsvFiles/Inputs/SinIn.csv");
            lnIn = new FileReader("src/lab2/resources/CsvFiles/Inputs/LnIn.csv");
            log2In = new FileReader("src/lab2/resources/CsvFiles/Inputs/Log2In.csv");
            log3In = new FileReader("src/lab2/resources/CsvFiles/Inputs/Log3In.csv");
            log5In = new FileReader("src/lab2/resources/CsvFiles/Inputs/Log5In.csv");
            log10In = new FileReader("src/lab2/resources/CsvFiles/Inputs/Log10In.csv");
            cotIn = new FileReader("src/lab2/resources/CsvFiles/Inputs/CotIn.csv");
            cscIn = new FileReader("src/lab2/resources/CsvFiles/Inputs/CscIn.csv");
            tanIn = new FileReader("src/lab2/resources/CsvFiles/Inputs/TanIn.csv");

            Iterable<CSVRecord> records = CSVFormat.DEFAULT.parse(secIn);
            for (CSVRecord record : records)
                Mockito.when(secMock.sec(Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(cosIn);
            for (CSVRecord record : records)
                Mockito.when(cosMock.cos(Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(sinIn);
            for (CSVRecord record : records)
                Mockito.when(sinMock.sin(Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(lnIn);
            for (CSVRecord record : records)
                Mockito.when(lnMock.ln(Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(log2In);
            for (CSVRecord record : records)
                Mockito.when(logMock.log(2, Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(log3In);
            for (CSVRecord record : records)
                Mockito.when(logMock.log(3, Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(log5In);
            for (CSVRecord record : records)
                Mockito.when(logMock.log(5, Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(log10In);
            for (CSVRecord record : records)
                Mockito.when(logMock.log(10, Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(cotIn);
            for (CSVRecord record : records)
                Mockito.when(cotMock.cot(Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(cscIn);
            for (CSVRecord record : records)
                Mockito.when(cscMock.csc(Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
            records = CSVFormat.DEFAULT.parse(tanIn);
            for (CSVRecord record : records)
                Mockito.when(tanMock.tan(Double.parseDouble(record.get(0)), functionEps)).thenReturn(Double.valueOf(record.get(1)));
        } catch (IOException ex) {
            System.err.println("IOException");
        }
    }

    @ParameterizedTest
    @ValueSource(doubles = {-10.0, -1.01, -1, -0.99, -0.01, 0, 10.0, 1.01, 1, 0.99, 0.01, Double.NaN, Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY})
    public void cosTest(double param) {
        Cos cos = new Cos();
        Assertions.assertEquals(Math.cos(param), cos.cos(param, eps), eps);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-10.0, -1.01, -1, -0.99, 10.0, 1.01, 1, 0.99, Double.NaN, Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY})
    public void cotTest(double param) {
        Cot cot = new Cot();
        Assertions.assertEquals(Math.cos(param) / Math.sin(param), cot.cot(param, eps), eps);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-10.0, -1.01, -1, -0.99, 10.0, 1.01, 1, 0.99, Double.NaN, Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY})
    public void cscTest(double param) {
        Csc csc = new Csc();
        Assertions.assertEquals(1 / Math.sin(param), csc.csc(param, eps), eps);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-10.0, -1.01, -1, -0.99, -0.01, 0, 1.01, 1, 0.99, Double.NaN, Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY})
    public void lnTest(double param) {
        Ln ln = new Ln();
        Assertions.assertEquals(Math.log(param), ln.ln(param, eps), eps);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-10.0, -1.01, -1, -0.99, -0.01, 0, 10.0, 1.01, 1, 0.99, Double.NaN, Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY})
    public void logTest(double param) {
        Log log = new Log();
        Assertions.assertEquals(Math.log(param) / Math.log(2), log.log(2, param, eps), eps);
        Assertions.assertEquals(Math.log(param) / Math.log(3), log.log(3, param, eps), eps);
        Assertions.assertEquals(Math.log(param) / Math.log(5), log.log(5, param, eps), eps);
        Assertions.assertEquals(Math.log10(param), log.log(10, param, eps), eps);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-10.0, -1.01, -1, -0.99, -0.01, 0, 10.0, 1.01, 1, 0.99, 0.01, Double.NaN, Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY})
    public void secTest(double param) {
        Sec sec = new Sec();
        Assertions.assertEquals(1 / Math.cos(param), sec.sec(param, eps), eps);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-10.0, -1.01, -1, -0.99, -0.01, 0, 10.0, 1.01, 1, 0.99, 0.01, Double.NaN, Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY})
    public void sinTest(double param) {
        Sin sin = new Sin();
        Assertions.assertEquals(Math.sin(param), sin.sin(param, eps), eps);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-10.0, -1.01, -1, -0.99, -0.01, 0, 10.0, 1.01, 1, 0.99, 0.01, Double.NaN, Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY})
    public void tanTest(double param) {
        Tan tan = new Tan();
        Assertions.assertEquals(Math.tan(param), tan.tan(param, eps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testSystemWithMocks(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithSec(double value, double expected) {
        Function function = new Function(new Sec(cosMock), lnMock, logMock, tanMock, cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithSecDeeper(double value, double expected) {
        Function function = new Function(new Sec(new Cos(sinMock)), lnMock, logMock, tanMock, cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithLn(double value, double expected) {
        Function function = new Function(secMock, new Ln(), logMock, tanMock, cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 20);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithLog(double value, double expected) {
        Function function = new Function(secMock, lnMock, new Log(), tanMock, cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 20);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithLogDeeper(double value, double expected) {
        Function function = new Function(secMock, lnMock, new Log(new Ln()), tanMock, cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 20);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithTan(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, new Tan(sinMock, cosMock), cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithTanDeeper(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, new Tan(new Sin(), new Cos(sinMock)), cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 5);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithTanDeeperAndCosDeeper(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, new Tan(new Sin(), new Cos(new Sin())), cosMock, cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 6);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithCos(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, new Cos(sinMock), cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithCosDeeper(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, new Cos(new Sin()), cotMock, sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 2);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithCot(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, cosMock, new Cot(sinMock, cosMock), sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithCotDeeper(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, cosMock, new Cot(new Sin(), new Cos(sinMock)), sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 11);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithCotDeeperAndCosDeeper(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, cosMock, new Cot(new Sin(), new Cos(new Sin())), sinMock, cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 15);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithSin(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, cosMock, cotMock, new Sin(), cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithCsc(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, cosMock, cotMock, sinMock, new Csc(sinMock));
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithCscDeeper(double value, double expected) {
        Function function = new Function(secMock, lnMock, logMock, tanMock, cosMock, cotMock, sinMock, new Csc(new Sin()));
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps);
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/CsvFiles/Inputs/SystemIn.csv")
    void testWithSinAndLn(double value, double expected) {
        Function function = new Function(secMock, new Ln(), new Log(), tanMock, cosMock, cotMock, new Sin(), cscMock);
        Assertions.assertEquals(expected, function.SystemSolve(value, functionEps), eps * 20);
    }
}