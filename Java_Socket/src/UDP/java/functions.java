package UDP.java;

public class functions {

    public static String getData(byte[] buffer) {
        StringBuilder data = new StringBuilder();
        for (byte b : buffer)
            if (b != 0)
                data.append((char) b);
        return String.valueOf(data);
    }
}
