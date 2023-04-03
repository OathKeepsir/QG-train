import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class CrudUtils {

    // 创建用户
    public static boolean createaccount(String name, int money) {
        ConnectionPool connectionPool = null;
        try {
            connectionPool = new ConnectionPool();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        // 获取连接
        Connection conn = null;
        try {
            conn = connectionPool.getConnection();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        PreparedStatement pstmt = null;
        try {
            conn = JDBCUtils.getConnection();
            String sql = "INSERT INTO account (name,money) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, name);
            pstmt.setInt(2, money);
            return pstmt.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            JDBCUtils.closeConnection(conn, pstmt);
        }
        return false;
    }

    // 查询所有用户
    public List<account> readAllUAccounts() {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        List<account> accountsList = new ArrayList<>();
        try {
            conn = JDBCUtils.getConnection();
            String sql = "SELECT * FROM account";
            pstmt = conn.prepareStatement(sql);
            rs = pstmt.executeQuery();
            while (rs.next()) {
                int id = rs.getInt("id");
                String name = rs.getString("name");
                int money = rs.getInt("money");
                account account = new account(id, name, money);
                accountsList.add(account);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            JDBCUtils.closeConnection(conn, pstmt, rs);
        }
        return accountsList;
    }

    // 更新用户
    public boolean updateaccount(int id, int newmoney, String newName) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            conn = JDBCUtils.getConnection();
            String sql = "UPDATE account SET name = ?, money= ? WHERE id = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, newName);
            pstmt.setInt(2, newmoney);
            pstmt.setInt(3, id);
            return pstmt.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            JDBCUtils.closeConnection(conn, pstmt);
        }
        return false;
    }

    // 删除用户
    public boolean deleteaccount(int id) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            conn = JDBCUtils.getConnection();
            String sql = "DELETE FROM account WHERE id = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, id);
            return pstmt.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            JDBCUtils.closeConnection(conn, pstmt);
        }
        return false;
    }
}
