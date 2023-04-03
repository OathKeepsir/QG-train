import java.io.IOException;
import java.io.InputStream;
import java.sql.*;
import java.util.Properties;

public class JDBCUtils {
    //基本的一些配置
    private static String URL;
    private static String Username;
    private static String Password;

    //注册驱动，加载驱动，为了不重复，所以使用static代码块
    static {
        try {
            // 加载并设置连接属性
            loadProperties();
            // 加载数据库驱动
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    private static void loadProperties() {
        Properties prop = new Properties();
        InputStream inputStream = JDBCUtils.class.getClassLoader().getResourceAsStream("jdbc.properties");
        if (inputStream != null) {
            try {
                prop.load(inputStream);
            } catch (IOException e) {
                e.printStackTrace();
            }
            URL = prop.getProperty("jdbc.url");
            Username = prop.getProperty("jdbc.username");
            Password = prop.getProperty("jdbc.password");
        } else {
            throw new RuntimeException("jdbc.properties not found");
        }
    }

    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(URL, Username, Password);//从驱动那里获得连接
    }

    public static void closeConnection(Connection conn, PreparedStatement ps, ResultSet rs) {
        try {
            if (rs != null) {
                rs.close();
            }
            if (ps != null) {
                ps.close();
            }
            if (conn != null) {
                conn.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    public static void closeConnection(Connection conn, PreparedStatement ps) {
        closeConnection(conn, ps, null);
    }

    public static void closeConnection(Connection conn) {
        closeConnection(conn, null, null);
    }

}
