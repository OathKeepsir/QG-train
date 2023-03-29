import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
@WebServlet("/demo1")
public class Servletdemo extends HttpServlet {
    protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String method = request.getParameter("method");
        System.out.println("内部method: " + method);
        switch (method) {
            case "post":
                doPost(request, response);
                break;
            case "update":
                doPut(request, response);
                break;
            case "delete":
                doDelete(request, response);
                break;
            case "connect":
                doConnect(request, response);
                break;
            case "options":
                doOptions(request, response);
                break;
            case "trace":
                doTrace(request, response);
                break;
            default:
                doGet(request, response);
                break;
        }

    }

    //实现GET请求
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            out.println("<!DOCTYPE html");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet Servletdemo</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>GET request successful!</h1>");
            out.println("</body>");
            out.println("</html>");
        } finally {
            out.close();
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (username != null && password != null) {
                response.setStatus(HttpServletResponse.SC_OK);
                out.println("登陆成功");
            } else {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                out.println("用户名或密码不能为空");
            }
        } finally {
            out.close();
        }
    }

    @Override
    protected void doPut(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            out.println("PUT request successful");
        } finally {
            out.close();
        }
    }

    @Override
    protected void doDelete(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            out.println("DELETE request successsful");
        } finally {
            out.close();
        }
    }

    @Override
    protected void doHead(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
    }

    private void doConnect(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            //只是返回一个消息用作展示
            out.println("CONNECT request successful");
        } finally {
            out.close();
        }

    }
    @Override
    protected void doOptions(HttpServletRequest request,HttpServletResponse response)
        throws ServletException,IOException{
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out=response.getWriter();
        try{
            response.setHeader("Allow","GET, POST, PUT, DELETE, HEAD, CONNECT, OPTIONS, TRACE");
            out.println("OPTIONS request successful!");
        }finally {
                out.close();
            }
        }
    @Override
    protected void doTrace(HttpServletRequest request,HttpServletResponse response)
        throws ServletException,IOException{
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out =response.getWriter();
        try{
            java.util.Enumeration<String>headerNames =request.getHeaderNames();
            while(headerNames.hasMoreElements()){
                String headerName =headerNames.nextElement();
                String headerValue =request.getHeader(headerName);
                out.println(headerName+";"+headerValue);
            }
            out.println("TRACE request successful!");
        }finally {
            out.close();
        }
        }
    }


