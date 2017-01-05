/*
 * csc678 hw 4 write a java program that interfaces with the Chinook database.
 USING JDBC to provide a simple online music store.
 
 */
package csc650hw4;

import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Scanner;

/**
 *
 * @author Karl
 */
public class Csc650hw4 {

    /**
     * @param args the command line arguments
     * @throws SQLException
     */
    public static void main(String[] args) throws SQLException {
        
        Scanner input = new Scanner(System.in);
        String choice = "";
        //the user will enter a "choice" that gets recorded in the String choice.
        while (choice.compareTo("exit") != 0) {
            System.out.println("Welcome to the Muzak store. Please select an option by its number or type 'exit' to quit the program.");
            System.out.println("1 - Obtain Album Title(s) based on artist name.\n"
                    + "2 - Obtain Track(s) of an Album Title.\n"
                    + "3 - Purchase History for a customer.\n"
                    + "4 - Update track price - Individual.\n"
                    + "5 - Update track price - Batch.");
            choice = input.next();

            switch (choice) {
                case "1":
                    getAlbumFromArtist();
                    break;
                case "2":
                    getTrackFromAlbum();
                    break;
                case "3":
                    getCustHist();
                    break;
                case "4":
                    updateTrackPriceInd();
                    break;
                case "5":
                    updateTrackPriceGroup();
                    break;
                case "exit":
                    break;
                default:
                    //if the user enters anything else, repeat the prompt.
                    System.out.println("please refer to options for appropriate input");
                    break;
            }

        }
    }
    /**
     * Given the artist name, retrieves the albums by this artist and displays them by artistId and Title.
     * @throws SQLException 
     */
    public static void getAlbumFromArtist() throws SQLException {
        Scanner input = new Scanner(System.in);
        String artistName = "error"; //the artist name to be searched
        Statement stmt = null;
        //counts the number of results from the sql Query.
        int count = 0;
        Connection c = null;
        ResultSet rs = null;
        try {
            //link Driver and connect to database
            Class.forName("org.sqlite.JDBC");
            c = DriverManager.getConnection("jdbc:sqlite:accounts.db");
            //retrieve user input.
            System.out.println("Please enter the name of the artist.");
            artistName = input.nextLine();
            stmt = c.createStatement();
            rs = stmt.executeQuery("SELECT A.Title,A.AlbumId FROM Album A, Artist B WHERE A.ArtistId=B.ArtistId AND B.Name=\'" + artistName + "\'");

            while (rs.next()) {
                System.out.print(rs.getInt("AlbumId") + "|" + rs.getString("Title"));
                count++;
                System.out.println();
            }
            rs.close();
            stmt.close();
            c.close();
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
        //case where no albums were found for this artist name.
        if (count == 0) {
            System.out.println("No Albums found for " + artistName);
        }
        System.out.println("\n");

    }

    /**
     * given an album name, displays the tracks from that album.  Then it provides an
     * option to purchase a track from this album, asking for track id and quantity.
     * If the transaction is successful, a new Invoice and InvoiceLine are added to their
     * respective tables.
     * @throws SQLException
     */
    public static void getTrackFromAlbum()  {
        Scanner input = new Scanner(System.in);
        String albumName;
        int count = 0;//counts number of results from initial sql query to get tracks.
        int tid; //trackid
        int cid = 25; //Victor Stevens.
        boolean isGood = false;
        int amount; //number to purchase
        double uPrice=0.0; //unitPrice of chosen track to purchase.
        double total=0;//total amount of purchase to put in Invoice.
        int maxInvoiceId; //the newest Invoice to be used in the InvoiceLine
        
        String choice = ""; //the user's text from the input.
        Statement stmt = null;
        Statement stmt1 = null;
        ResultSet rs = null,
                rs1 = null;
        Connection c = null;
        try {
            Class.forName("org.sqlite.JDBC");

            c = DriverManager.getConnection("jdbc:sqlite:Chinook.db");
            
            System.out.println("please enter the album name.");
            albumName = input.nextLine();
            stmt = c.createStatement();
            stmt1 = c.createStatement();
            rs = stmt.executeQuery("SELECT T.Name,T.TrackId,T.GenreId,T.UnitPrice FROM Track T, Album A WHERE A.Title=\'" + albumName + "\' AND T.AlbumId = A.AlbumId");
            while (rs.next()) {
                rs1 = stmt1.executeQuery("SELECT G.Name FROM Genre G, Track T WHERE G.GenreId=" + rs.getInt("GenreId"));
                //TrackName|TrackId|GenreName|UnitPrice
                System.out.println(rs.getString("Name") + "|" + rs.getInt("TrackId") + "|" + rs1.getString("Name") + "|" + rs.getDouble("UnitPrice"));
                count++;
            }
            if (count > 0) {
                //allow them to purchase. prompt for track id and quantity, then update records accordingly.

                System.out.println("To purchase a track, enter '1', otherwise, type 'exit'.");
                //if the input is "exit" quit.
                while (choice.compareTo("exit") != 0) {
                    choice = input.next();
                    //making a purchase
                    if (choice.compareTo("1") == 0) {
                        //prompt for TrackId
                        System.out.println("enter the trackId to purchase.");
                        tid = input.nextInt();
                        System.out.println("enter how many you wish to purchase.");
                        amount = input.nextInt();
                        //check if tid is valid from the Resultset of the first query.
                        rs=stmt.executeQuery("SELECT T.Name,T.TrackId,T.GenreId,T.UnitPrice FROM Track T, Album A WHERE A.Title=\'" + albumName + "\' AND T.AlbumId = A.AlbumId");
                        while (rs.next()) {
                            if (rs.getInt("TrackId") == tid) {
                                uPrice = rs.getDouble("UnitPrice");
                                isGood = true;
                            }
                        }
                        if (amount <= 0) {
                            isGood = false;
                        }
                        //once everything checks out, make the transaction; update the records. update Invoice, InvoiceLine, with customer info.
                        if (isGood == true) {
                            total = amount * uPrice;
                            //InvoiceDate = today's datetime.
                            //CustomerId,BillingAdress, BillingCity, BillingState, BillingCountry, BillingPostalCode
                            //make an invoice, using the total by multiplying amount with unitprice of the track that was selected.
                            //updating the Invoice table, then the InvoiceLine table.
                            
                            rs = stmt1.executeQuery("SELECT * FROM Customer WHERE CustomerId =25"); //getting info to put in invoice,
                            
                            stmt1.executeUpdate("INSERT INTO Invoice (CustomerId,InvoiceDate,BillingAddress,BillingCity,BillingState,BillingCountry,BillingPostalCode,Total) "
                                    + "VALUES ("+rs.getInt("CustomerId")+",2015-12-09,\'"+rs.getString("Address")+"\',\'"+rs.getString("City")+"\',\'"+rs.getString("State")+"\',\'"+rs.getString("Country")+"\',\'"+rs.getString("PostalCode")+"\',"+total+")");
                            //we need InvoiceId, TrackId, UnitPrice, Quantity.  InvoiceId comes from the most recent Invoice, which should be the highest id value.
                            rs1 = stmt1.executeQuery("SELECT MAX(InvoiceId) AS A FROM Invoice");
                            rs1.next();
                            maxInvoiceId= rs1.getInt("A") ;
                            
                            stmt1.executeUpdate("INSERT INTO InvoiceLine (InvoiceId, TrackId, UnitPrice, Quantity) "
                                    + "VALUES ("+maxInvoiceId+","+tid+","+uPrice+","+amount+")");
                            
                            System.out.println("your transaction was successful, we hope you enjoy your purchase.");
                            //successful operation exits loop to finish method
                            choice = "exit";
                        } else {
                            System.out.println("Error: Track id is incorrect or quantity is <= 0.");
                            choice = "exit";
                        }
                    } else if(choice.compareTo("exit") ==0){
                    }else{
                        System.out.println("To purchase a track, enter '1', otherwise, type 'exit'.");
                    }
                }
            } else {
                //no tracks for that album name,
                System.out.println("Sorry, there are no tracks for that album title.");
            }
            rs.close();
            rs1.close();
            stmt.close();
            stmt1.close();
            c.close();
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
    }
    //look at invoice using cid, then look at InvoiceLine to get the track name and quantity, then look at track to get Album name
    /**
     * Using customerid, finds the invoiceLines pertaining to this customer and displays purchase history of tracks.
     */
    public static void getCustHist() {
        Scanner input = new Scanner(System.in);
        int custId = -1; //the artist name to be searched
        Statement stmt = null;
        Statement stmt1 = null;
        int count = 0;
        Connection c = null;
        ResultSet rs = null;
        ResultSet rs1 = null;
        try {
            Class.forName("org.sqlite.JDBC");
            c = DriverManager.getConnection("jdbc:sqlite:chinook.db");

            System.out.println("Please enter a customer id.");
            custId = input.nextInt();
            stmt = c.createStatement();
            stmt1 = c.createStatement();
            rs = stmt.executeQuery("SELECT InvoiceId, InvoiceDate  "
                    + "FROM Invoice "
                    + "WHERE CustomerId="+custId+"" );
            //System.out.println(rs.getString("InvoiceDate"));
            while(rs.next()){
            //after getting InvoiceId, get the trackId and quantity from InvoiceLine for each purchase
                //System.out.println(rs.getString("InvoiceDate"));
                rs1 = stmt1.executeQuery("SELECT L.TrackId,L.Quantity,T.Name, A.Title "
                    + "FROM InvoiceLine L, Track T, Album A "
                    + "WHERE L.InvoiceId=" + rs.getInt("InvoiceId") + " AND L.TrackId=T.TrackId AND T.AlbumId=A.AlbumId");
            
                //get the Track, using trackId
                rs1.next();
                System.out.print(rs1.getString("Name")+"|Album:"+rs1.getString("Title")+"|Date: ");
                System.out.print(rs.getString("InvoiceDate"));//rs.getString("InvoiceDate")+
                System.out.println("|Quantity: "+rs1.getInt("Quantity"));
                count++;
            }
            rs.close();
            rs1.close();
            stmt.close();
            c.close();
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
        if (count == 0) {
            System.out.println("No purchase history found for " + custId);
        }
        System.out.println("\n");

    }

    /**
     * Updates an individual track price when given a trackId'
     * Prompts the user for a track id, diplays the current unitprice of the track, if valid.
     * Then prompts for a new price >= zero and updates the record with the new price.
     * 
     */
    public static void updateTrackPriceInd() {
        Scanner input = new Scanner(System.in);
        int trackId = 0; //the trackid to update
        Statement stmt = null;
        /**
         * the new price to update the track's unitprice.
         */
        double newPrice;
        /**
         * check for valid result, if no results, prompts error message.
         */
        int count = 0;
        Connection c = null;
        ResultSet rs = null;
        try {
            Class.forName("org.sqlite.JDBC");
            c = DriverManager.getConnection("jdbc:sqlite:chinook.db");
            //prompt user for track id.
            System.out.println("Please enter the track id you wish to update.");
            trackId = input.nextInt();
            stmt = c.createStatement();
            //obtaining original unitprice using trackid.
            rs = stmt.executeQuery("SELECT UnitPrice FROM Track WHERE TrackId="+trackId);

            if (rs.next()) {
                System.out.println("current unit price for trackid "+trackId+": $"+rs.getDouble("UnitPrice") );
                count++;
                System.out.println("Please enter new unitprice for this track.");
                newPrice = input.nextDouble();
                //checking input for a non-negative price. else, exit method.
                if(newPrice < 0.0){
                    System.out.println("error: new price must be greater than or equal to zero.");
                }else{
                    stmt = c.createStatement();
                    
                    stmt.executeUpdate("UPDATE Track SET UnitPrice="+newPrice+" WHERE TrackId="+trackId);
                    rs = stmt.executeQuery("SELECT UnitPrice FROM Track WHERE TrackId="+trackId);
                    rs.next();
                    System.out.println("new price for trackid "+trackId+" is $"+rs.getDouble("UnitPrice"));
                }
            }
            rs.close();
            stmt.close();
            c.close();
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
        if (count == 0) {
            System.out.println("No unitprice found for trackid "+trackId);
        }
        System.out.println("\n");
    }
//prompt for percentage value
    //valid input is -100 to 100
    //track id, track name, previous unit price, updated unit price
    /**
     * updates all prices by a percentage amount specified by the user.
     */
    public static void updateTrackPriceGroup() {
        Scanner input = new Scanner(System.in);
        int trackId = 0; //the trackid to update
        Statement stmt = null;
        Statement stmt1 = null;
        Statement stmt2 = null;
        /**
         * the percentage to change the unitPrice from -100 to 100.
         */
        int percent;
        double[] oldPrices;
        double percentChange;
        boolean isIncrease = false;
        double newPrice;
        double oldPrice;
        int count = 0;
        /**
         * check for valid result, if no results, prompts error message.
         */
        Connection c = null;
        ResultSet rs = null;
        ResultSet rs1 = null;
        try {
            Class.forName("org.sqlite.JDBC");
            c = DriverManager.getConnection("jdbc:sqlite:chinook.db");
            //prompt user for percentage
            System.out.println("Please enter the percentage you wish to change the unitprice of all tracks, (as -100 to 100).");
            percent = input.nextInt();
            percentChange = percent/100.0;
            
            //checking value range.
            if(percentChange > 1.0 || percentChange < -1.0){
                System.out.println("error: enter a value from -100 to 100.");
                return;
            }
            //percentage change is checked for positive negative
            if(percentChange<0.0){
                percentChange=percentChange*(-1.0);
            }else if(percentChange>=0.0){
                isIncrease=true;
            }
            stmt = c.createStatement();
            stmt1 = c.createStatement();
            stmt2 = c.createStatement();
            //obtaining original unitprice of all tracks and their trackIds
            rs = stmt.executeQuery("SELECT TrackId, UnitPrice FROM Track");
            rs1 = stmt1.executeQuery("SELECT UnitPrice FROM Track");
            System.out.println("please wait: this may take about 5-10 minutes.");
            //for every track, change its unitPrice.
            while (rs.next()) {
                oldPrice = rs.getDouble("UnitPrice");
                newPrice = oldPrice*percentChange;
                if(isIncrease == true){
                    //positive change
                    newPrice = newPrice+oldPrice;
                    
                    //checking input for a non-negative price. else, exit method.
                    stmt2.executeUpdate("UPDATE Track SET UnitPrice="+newPrice+" WHERE TrackId="+rs.getInt("TrackId"));
                    
                }else{
                    //its a negative change.
                    newPrice = oldPrice - newPrice;
                    stmt2.executeUpdate("UPDATE Track SET UnitPrice="+newPrice+" WHERE TrackId="+rs.getInt("TrackId"));
                }
                count++;
            }
            //displaying number of records updated.
            System.out.println("number of records updated: "+count);
            
            //displaying all updated records.
            /*rs = stmt.executeQuery("SELECT TrackId, Name, UnitPrice FROM Track");
            while(rs.next() && rs1.next()){
                System.out.println("TrackId: "+rs.getInt("TrackId")+"|Name: "+rs.getString("Name")+"|oldPrice: "+rs1.getDouble("UnitPrice")+"|newPrice: "+rs.getDouble("UnitPrice"));
            }*/
            System.out.println();
            rs.close();
            stmt.close();
            stmt1.close();
            stmt2.close();
            c.close();
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
        
        System.out.println("\n");
    }
}
