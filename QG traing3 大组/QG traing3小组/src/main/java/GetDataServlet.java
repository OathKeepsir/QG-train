import com.google.gson.Gson;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.net.http.HttpClient;

@WebServlet("/getData")
public class GetDataServlet extends HttpServlet {
    private static final long serialVersionUID =1L;
    protected void doGet(HttpServlet request, HttpServletResponse response)throws ServletException, IOException{
        UserData userData =new UserData("John Doe",30,"New York");
        Gson gson=new Gson();
        String json = gson.toJson(userData);

        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write(json);
    }
}
