import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Properties;
public class ConnectionPool {
    private static  String URL;
    private static  String Username;
    private static  String Password;
    private static final int INITIAL_POOL_SIZE = 10;
    //这一部分是为了方便统一修改配置，所以使用文件properties，然后这一段直接抄的JDBCUtils里面的代码，应该问题不大。
    //创建prop，用IO流接收配置文件，再将配置加载进prop对象中，prop再赋给URL等变量
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
            //如果inputStream为null，即无法找到jdbc.properties文件，程序将抛出一个RuntimeException并附带一条描述性消息，表明文件未找到。当这个异常被抛出时，程序会立即终止执行，并显示异常堆栈跟踪信息。
        }
    }

    private final Queue<Connection> connectionQueue;
//提前准备好连接，最大数量可自己调整
    public ConnectionPool() throws SQLException {
        loadProperties();
        connectionQueue = new LinkedList<>();
        for (int i = 0; i < INITIAL_POOL_SIZE; i++) {
            connectionQueue.add(createNewConnection());
        }
    }

    private Connection createNewConnection() throws SQLException {
        return DriverManager.getConnection(URL,Username,Password);
    }

    public Connection getConnection() throws SQLException {
        if (connectionQueue.isEmpty()) {
            return createNewConnection();
        } else {
            return connectionQueue.poll();
        }
    }

    public void releaseConnection(Connection connection) {
        if (connection != null) {
            connectionQueue.offer(connection);
        }
    }
}
