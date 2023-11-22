import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class Main {
    public static void main(String[] args) throws IOException {
        System.out.println("""
                Дисциплина: Тестирование ПО
                Лабораторная №2
                Вариант: 75123
                Автор: Неграш А.В., P33301
                """);

        PrintWriter writer = new PrintWriter("output.csv", StandardCharsets.UTF_8);
        Function function = new Function();
        double count = -10.0;
        while (count <= 10){
            writer.println(count + ", " + function.SystemSolve(count, 0.1));
            count = count + 0.1;
        }
        writer.close();
    }
}