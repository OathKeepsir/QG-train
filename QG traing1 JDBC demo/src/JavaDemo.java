

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class JavaDemo {
    public static void main(String[] args) {
        // 声明数据库连接、预编译语句和结果集对象
        Connection conn = null;
        PreparedStatement pstmt = null;//这个可以防止注入，与普通的Statement相比。
        ResultSet rs = null;

        try {
            // 获取数据库连接
            conn = JDBCUtils.getConnection();
            // 编写SQL查询语句
            String sql = "SELECT * FROM account";
            // 使用Connection对象的prepareStatement方法创建PreparedStatement对象
            pstmt = conn.prepareStatement(sql);
            // 执行查询语句并返回结果集
            rs = pstmt.executeQuery();

            // 遍历结果集
            while (rs.next()) {
                // 获取结果集中的id和name字段的值
                int id = rs.getInt("id");
                String name = rs.getString("name");
                double money =rs.getDouble("money");
                // 打印结果
                System.out.println("ID: " + id + ", Name: " + name +", Money" + money);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            // 不管是否发生异常，都需要关闭数据库资源
            JDBCUtils.closeConnection(conn, pstmt, rs);
        }
    }
}

