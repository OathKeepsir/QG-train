import java.util.List;

public class CrudDemo {
    public static void main(String[] args) {
        CrudUtils crudUtils = new CrudUtils();

        // 创建用户
        System.out.println("创建用户：");
        CrudUtils.createaccount("三", 2000);
        crudUtils.createaccount("李四", 3000);

        // 查询所有用户
        System.out.println("查询所有用户：");
        List<account> accounts = crudUtils.readAllUAccounts();
        for (account account : accounts) {
            System.out.println(account);
        }

        // 更新用户
        System.out.println("更新用户：");
        crudUtils.updateaccount(1, 1000, "王五");

        // 查询所有用户
        System.out.println("查询更新后的所有用户：");
        accounts = crudUtils.readAllUAccounts();
        for (account account : accounts) {
            System.out.println(account);
        }

        // 删除用户
        System.out.println("删除用户：");
        crudUtils.deleteaccount(2);

        // 查询所有用户
        System.out.println("查询删除后的所有用户：");
        accounts = crudUtils.readAllUAccounts();
        for (account account : accounts) {
            System.out.println(account);
        }
        System.out.println("嗨");
    }
}

