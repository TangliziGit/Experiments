import java.util.*;
import java.io.*;
import java.text.*;
import java.sql.*;

/**
 * A class representing the driver program to the
 * SSD7 transaction exercise.
 *
 * @author CTE
 * @version 1.0
 */

public class MovieTransaction
{
    /**
     * main method.
     *
     */
    public static void main( String [] args )
    {

	String [] movienames = new String[10];
	String [] movietimes = new String[10];
	String sqlquery = null;
	String moviename = null;
	String movietime = null;
	ResultSet rset = null;
	Connection conn = null;
	Statement stmt = null;
	BufferedReader keyIn = null;
	String url = "jdbc:postgresql:movie";
	String username = "vince";
	String password = "";
	int position = 0, choice, movie_id, numseats, availableseats;

	try
	    {
		// Create a BufferedReader to read input from the keyboard.
		keyIn = new BufferedReader(new InputStreamReader(System.in));

		// Load the PostgreSQL JDBC driver
		Class.forName("org.postgresql.Driver");

		// Create a connection to the database.
		conn = DriverManager.getConnection( url, username,password );

		// Create a statement object.
		stmt = conn.createStatement();


		System.out.println( "Welcome to the movie theater!" );




        // Begin a new, chained, transaction.
        /*
		* ####################################################
		* 事务1, 查询所有电影
		* 1. 在查询前开始，在显示信息后结束
		*
		* 2.
		* 将用户选择喜欢观看的电影的操作排除在事务外，因此这个查询单独作为一个事务，
		* 同时rset的方法需要在事务中执行
		*
		* 3. 因为此事务只有一个语句且为查询语句，本身就是可串行化的，所以不存在不可重复读和幻读问题，设置为read committed.
		* ####################################################
		*/

        stmt.executeUpdate( "Begin Work" );
        stmt.executeUpdate( "set transaction isolation level read committed " );

		// Query the titles currently playing.
		String SQLQuery = "select distinct title from movie";
		rset = stmt.executeQuery( SQLQuery );

		while( rset.next() )
		    {
			movienames[rset.getRow()] = rset.getString( "title" );
			System.out.println( rset.getRow() + ": " + rset.getString("title") );
		    }
		stmt.executeUpdate("commit");





			// Ask the user what movie he wants to see.
		System.out.print( "Enter the number of the movie you want to see:" );
		choice = Integer.parseInt(keyIn.readLine());
		moviename = movienames[(choice)];



        /* ####################################################
         * 事务2, 查询某电影下的所有场次
         * 1. 在查询前开始，在应用获得信息后结束
         *
         * 2.
         * 将用户选择相应场次的操作排除在事务外，因此这个查询单独作为一个事务
		 * 同时rset的方法需要在事务中执行
		 *
         * 3. 因为此事务只有一个语句且为查询语句，本身就是可串行化的，所以不存在不可重复读和幻读问题，设置为read committed.
         * ####################################################
         */
        stmt.executeUpdate( "Begin Work" );
        stmt.executeUpdate( "set transaction isolation level read committed " );

		// Query the id for this movie.
		sqlquery = new String( "select movie_id from movie where title='" + moviename + "'" );
		rset = stmt.executeQuery( sqlquery );

        rset.next();
        movie_id = rset.getInt( "movie_id" );
		stmt.executeUpdate("commit");





		// Query the available times for the chosen movie.
		sqlquery = new String( "select distinct movie_time from showing where movie_id =" + movie_id );
		rset = stmt.executeQuery( sqlquery );
		while( rset.next() )
		    {
			movietimes[(rset.getRow())] = rset.getString( "movie_time" );
                        System.out.println( rset.getRow() + ": " + rset.getString( "movie_time" ) );
                    }
		// Ask the user what showing he wants to see.
		System.out.println( "Enter the number of the time you want to see: " );
		choice = Integer.parseInt( keyIn.readLine() );
		movietime = movietimes[(choice)];

		// Ask the user how many seats he wants.
		System.out.println( "Please enter the number of seats that you want to buy: " );
		numseats = Integer.parseInt( keyIn.readLine() );




        /* ####################################################
         * 事务3, 查询系统查询剩余票数，如果有剩余票，进行购买操作。
         * 1. 在查询前开始
         * 若判断无剩余票后，在应用程序显示信息前结束事务
		 * 若判断有剩余票后，继续进行购买操作（即更新座位数）后结束事务
         *
         * 2. 事务边界设置的原因有两点
         * 首先将用户输入购票张数的操作排除在事务外，因此这一次查询和一次更新单独作为一个事务
         * 其次用户对应的业务是购买电影票，所以查询剩余个数和更新票数是不能拆开的，
         *
         * 3. 应设置为repeatable read，原因两点
         * 首先，此处可能遇到更新丢失问题，可以使用repeatable read或serializable。
         * 更新丢失问题，即有两个事务读到同一数据，其中一个首先对此数据减一然后提交，另一个事务等待锁然后提交减一的操作，结果此数据只减少一次。
         * 为了解决此问题，应采用repeatable read或serializable
         *
         * 其次，为了最大化并发性，采用repeatable read隔离方式
		 * ####################################################
         */
        stmt.executeUpdate( "Begin Work" );
        stmt.executeUpdate( "set transaction isolation level repeatable read " );

		// Query the database for the number of available standrd seats.
		sqlquery = new String( "select available_standard_seats from showing where movie_id = " + movie_id );
		rset = stmt.executeQuery( sqlquery );
		rset.next();
		availableseats = rset.getInt( "available_standard_seats" );

		if (availableseats < numseats)
		    {
            stmt.executeUpdate( "rollback" );
			System.out.println( "We are sorry, there are not that many seats available for this showing!" );
			System.out.println( "Please try again!" );
			conn.close();
			System.exit(0);
		    }
		// If there are enough available seats, update the database for the reservation and commit the transaction.
		else
		    {
			sqlquery = new String( "update showing set available_standard_seats=" + (availableseats-numseats) + " where movie_id=" + movie_id + " and movie_time='" + movietime + "'" );
			stmt.executeUpdate( sqlquery );
			stmt.executeUpdate( "commit" );
			System.out.println( "Your tickets have now been purchased, enjoy the show!" );
			conn.close();
		    }
	    }


	catch( SQLException e )
	    {
		System.out.println( "An exception has occured!" );
		e.printStackTrace();
		try
		    {
			stmt.executeUpdate("rollback");
			conn.close();
		    }
		catch( Exception exception )
		    {
			exception.printStackTrace();
		    }
		System.out.println( "Transaction has been rolled back!" );
	    }
	catch( Exception e )
	    {
		System.out.println( "A non database error has occured!" );
		try
		    {
			stmt.executeUpdate("rollback");
			conn.close();
		    }
		catch( Exception exception )
		    {
			exception.printStackTrace();
		    }
		System.out.println( "Transaction has been rolled back!" );
		e.printStackTrace();
	    }
    }
}
