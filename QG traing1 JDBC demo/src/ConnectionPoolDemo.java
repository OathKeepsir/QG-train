import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class ConnectionPoolDemo {
    public static void main(String[] args) {
        try {
            ConnectionPool connectionPool = new ConnectionPool();

            // 获取连接
            Connection connection = connectionPool.getConnection();

            // 使用连接进行数据库操作
            //尝试了一下，其实我觉得这里应该不用特地写一个demo出来，ConnectionPool其实就是提供一个connection ,提前准备好的，然后在其他文件
            //如CrudDemo里面，把直接创建的connection 换成调用ConnectionPool.getConnection,即可，其他的保持一致，正常使用即可。
            //现在在CrudUtils里面直接修改展示一下
            //小插曲，学习记录，本来想在这里写一个函数，结果报错了，原来java里面，main函数里头不能直接定义一个函数。
            // 释放连接
            connectionPool.releaseConnection(connection);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    //学习记录，没有学习过异常这个知识点：try-catch 代码块用于捕获和处理异常。在可能抛出异常的代码周围使用 try 关键字，然后在紧随其后的 catch 代码块中处理异常。这样，当异常发生时，程序不会立即终止，而是会执行 catch 代码块中的代码以处理异常。
    //throws 关键字将异常传递给调用者。调用者需要处理异常，或者继续将其传递给它的调用者。这样，异常处理可以在适当的地方进行，而不是在每个方法内部。
    //总结：throws 关键字用于声明方法可能抛出的异常类型，允许调用者处理异常。
    //try-catch 代码块用于捕获和处理异常，防止程序在异常发生时立即终止。
}
