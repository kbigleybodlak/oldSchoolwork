/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package csc650projectcbc;

/**
 *
 * @author Karl
 */
import java.util.Arrays;
import javax.crypto.Cipher;
//import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.util.Scanner;

import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;
//import sun.misc.BASE64Decoder;
//import sun.misc.BASE64Encoder;
//import java.util.Arrays;
//import javax.xml.bind.DatatypeConverter;
//import java.math.BigInteger;

public class Csc650projectOFB {

    /*
    
    in this one 
    after padding the right with zeroes to make it 64 bits,
    convert the hex string IV to a byte array.
    run the IV through DES
    turn that byte array into a binary string.
    
    pad the key same as CBC, so that it is used as the key.
     
    after converting the message to a binary string,
    pad it out with zeroes so its a multiple of k bits.
    
    convert the IV to a binary string.
    
    
    first send the iv through the DES.
    iv in the first iteration comes from user
    after that its the previous ciphertextblock.
    
    after the encryption of IV, use a subarray of k most-significant bits from it
    and xor it with a k-bit block from the message
    
    */
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        // TODO code application logic here
        
        Scanner input = new Scanner(System.in);
        System.out.println("test CFB encoder, please only use hexidecimal values.");
        System.out.println("please type message to be encrypted.");
        String m = input.nextLine();
        System.out.println("Please type key of length 16 or longer to use for DES encryption. otherwise the string is padded with zeroes");
        String key = input.nextLine();
        System.out.println("Please type the initial vector as a String (16 hex digits). This will be padded to 64 bits by adding zeroes to the left of the IV if not long enough for DES.");
        String IV = input.nextLine();
        System.out.println("Please type the int for k. 1<=k<=64.");
        int k = input.nextInt();
        if(k<1 || k>64){
            System.out.println("error: 1<k<64");
        }else{
        System.out.println(ofb(m,key,IV,k));
        }
    }
    
    public static String ofb(String m, String key, String IV, int k) throws Exception{
        String finalString="";
        int i;
        String em = "";
        int j = 0;
        //the array that will hold the integers of the message
        int[] messageInts;
        String padding = "0";
        boolean is16Key = true;
        boolean is16Msg = true;
        String xorElement="";
        String pieceForDES="";
        byte[] messageBytes;
        byte[] ivBytes;
        byte[] bytesForDES;
        //the case when the key is not long enough. pad it out.

        //figure out how many 0s to pad the last block and the key so its 64 bits.
        int numToPad;
        String messagePiece;
        String ivPiece;
        int ivPieceInt;
        if (key.length()<16){
            numToPad = 16-key.length(); // so if key length is 14, numtopad is 2
            while(is16Key){
                key = padding + key;
                numToPad = numToPad - 1;
                if(numToPad<=0){
                    is16Key = false;
                }
            }
            System.out.println("key padded to: "+key);
        }
        if(key.length()>16){
            key = key.substring(0, 16);
        }
        //is16Key=true;
        byte[] keyDES = hexStringToByteArray(key);
        DesEncrypter encrypto = new DesEncrypter(keyDES);
        //**********************key padding and encryption init done.
        
        //*******************converting message to bit string, then padding it to a multiple of k bits.  so if k=3  and its 1111 1111 1111 1111, pad it to 00 1111 1111 1111 1111
        m = hexToBinaryString(m);
        if(m.length()%k>0){
            numToPad = k-(m.length()%k);
            for(i=0;i<numToPad;i++){
                m= padding +m;
            }
            System.out.println("message padded to:  " + m);
        }
        
        //**********padding the IV to 64  bits if it is smaller than 64 bits.
        //IV = hexToBinaryString(IV);
        if((IV.length())%16>0 && IV.length()<16){
            
            numToPad = 16-((IV.length())%16);
            
            System.out.println(IV.length() +"  "+ numToPad);
            for(i=0;i<numToPad;i++){
                IV= padding +IV;
                
            }
            System.out.println("IV padded to:  " + IV);
        }else{
            IV = IV.substring(0,16);
        }
        
        
        
        //*******determine number of rounds to go through by how many k-bit blocks there are.
        int numBlocks = m.length()/k;
        
        
        
        //*********BEGIN EXECUTION LOOP
        String subIV;
        String subMsg;
        for(i=0;i<numBlocks;i++){
            //first iteration, skip the step where you concat the ciphertext block to the end of the IV.
            
                ivBytes = hexStringToByteArray(IV);
            
            xorElement = "";
            ivBytes = encrypto.encrypt(ivBytes);
            IV = hexToBinaryString(IV);
            //constructing the encrypted IV into a bitstring: xorElement.
            for(j=0;j<ivBytes.length;j++)
                xorElement = xorElement + byteToBinString(ivBytes[j]);   ////byteToBinString does as its supposed to.
            //System.out.println(xorElement);
            
            //getting the substring that will be xored with the k bits of plaintext.
            subIV = xorElement.substring(0, k); //PRINTINg correct amount
            //System.out.println("subIV:  "+subIV);
            
            //creating the next IV to be used for encryption.  IV should stay at 64 bits.
            if(IV.length()>k){
                IV = IV +subIV;
                IV = IV.substring(k, IV.length());//has correct amount.
                //System.out.println("run "+i+":  "+IV);
                
            //aka. the k is 64 bits. 
            }else{
                IV = xorElement;
            }
            
            //getting next k bits to encrypt from plaintext.
            subMsg = m.substring(i*k, i*k+k);
            
            //******ENDING ITERATION UPDATE.
            finalString = finalString + xorBinaryStrings(subMsg,subIV);
            IV = binaryToHexString(IV);
        }
        
        finalString = binaryToHexString(finalString);
        return finalString;
    }
    
    //Xor operation on two strings representing a binary sequence.
    public static String xorBinaryStrings(String msg, String iv){
        int i;
        String xorMsg="";
        char bit1;
        char bit2;
        for(i=0;i<msg.length();i++){
            bit1 = msg.charAt(i);
            bit2 = iv.charAt(i);
            if(bit1!=bit2 && ((bit1=='1') || (bit2=='1'))){
                xorMsg = xorMsg + "1";
            }else{
                xorMsg = xorMsg + "0";
            }
        }
        return xorMsg;
    }
    
    public static byte[] concat(byte[] a, byte[] b) {
        int aLen = a.length;
        int bLen = b.length;
        byte[] c= new byte[aLen+bLen];
        System.arraycopy(a, 0, c, 0, aLen);
        System.arraycopy(b, 0, c, aLen, bLen);
        return c;
    }
    
    public static String binaryToHexString(String binString){
        String piece;
        String padding ="0";
        String finalString = "";
        int i;
        if(binString.length()%4>0){
            int numToPad = 4-(binString.length()%4);
            for(i=0;i<numToPad;i++){
                binString = padding + binString;
            }
        }
        for(i=0;i<binString.length()/4;i++){
            piece = binString.substring(4*i, 4*i+4);
            switch(piece){
                case "0000":
                    finalString = finalString+"0";
                    break;
                case "0001":
                    finalString = finalString+"1";
                    break;
                case "0010":
                    finalString = finalString+"2";
                    break;
                case "0011":
                    finalString = finalString+"3";
                    break;
                case "0100":
                    finalString = finalString+"4";
                    break;
                case "0101":
                    finalString =finalString+"5";
                    break;
                case "0110":
                    finalString = finalString+"6";
                    break;
                case "0111":
                    finalString = finalString+"7";
                    break;
                case "1000":
                    finalString = finalString+"8";
                    break;
                case "1001":
                    finalString = finalString+"9";
                    break;
                case "1010":
                    finalString = finalString+"a";
                    break;
                case "1011":
                    finalString = finalString+"b";
                    break;
                case "1100":
                    finalString = finalString+"c";
                    break;
                case "1101":
                    finalString = finalString+"d";
                    break;
                case "1110":
                    finalString = finalString+"e";
                    break;
                case "1111":
                    finalString = finalString+"f";
                    break;
                
            }
        }
        return finalString; 
    } 
    
    public static byte[] hexStringToByteArray(String s){
        //every Character is 4 bits or 1/2 of  a byte.
        byte[] byteForDES = new byte[s.length()/2];
        int i,j,k;
        char nibble;
        String sub;
        byte insert = 0;
        //decode the message char by char. after every 2 chars, they create another byte to put in the byte array.
        for(i=0; i<byteForDES.length;i++){
            sub = s.substring(2*i, 2*i+2);
            //adding nibbles to the byte.
            insert =0;
            for(j=1,k=0;j>=0 && k<2;j--,k++){
                //0,1 is a byte, 2,3 is a byte, etc.
                nibble = s.charAt(2*i+k);
                switch(nibble){
                    case '0':
                        break;
                    case '1':
                    insert = (byte) (((int)insert & 0xFF) | 0x01);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));  
                        break;
                    case '2':
                    insert = (byte) (((int)insert & 0xFF) | 0x02);
                        insert = (byte) (((int)insert & 0xFF)  << (4*j));                       
                        break;
                    case '3':
                    insert = (byte) (((int)insert & 0xFF) | 0x03);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                    case '4':
                    insert = (byte) (((int)insert & 0xFF) | 0x04);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case '5':
                    insert = (byte) (((int)insert & 0xFF) | 0x05);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case '6':
                    insert = (byte) (((int)insert & 0xFF) | 0x06);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case '7':
                    insert = (byte) (((int)insert & 0xFF) | 0x07);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case '8':
                    insert = (byte) (((int)insert & 0xFF) | 0x08);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case '9':
                    insert = (byte) (((int)insert & 0xFF) | 0x09);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case 'a' | 'A':
                    insert = (byte) (((int)insert & 0xFF) | 0x0A);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case 'b' |'B':
                    insert = (byte) (((int)insert & 0xFF) | 0x0B);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case 'c' | 'C':
                    insert = (byte) (((int)insert & 0xFF) | 0x0C);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case 'd' | 'D':
                    insert = (byte) (((int)insert & 0xFF) | 0x0D);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case 'e' | 'E':
                    insert = (byte) (((int)insert & 0xFF) | 0x0E);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                case 'f' |'F':
                    insert = (byte) (((int)insert & 0xFF) | 0x0F);
                        insert = (byte) (((int)insert & 0xFF) << (4*j));                       
                        break;
                }
                                        //System.out.println("insert after a byte: " +insert);

            }
            //System.out.println(insert);
            byteForDES[i]=insert;
            //System.out.println(byteForDES[i]);
            //System.out.println("the returned array so far" + byteForDES);
            
        }
        return byteForDES;
    }
   
   
   
   public static String byteToBinString(byte desByte){
       
       byte b1 = desByte;
       String s1 = String.format("%8s", Integer.toBinaryString(b1 & 0xFF)).replace(' ', '0');
       return s1;
       
       
   }
    
    //converts 1 byte to a hexidecimal string (aka 2 chars).
    public static String byteToHexString(byte desByte){
        String bstring ="";
        byte upper = desByte;
        byte lower;
        upper = (byte) (((int)upper & 0xff) >>> 4);
        lower = desByte;
        lower = (byte) (((int)lower & 0xff) << 4);
        lower = (byte) (((int)lower & 0xff) >>> 4);
        
        bstring = halfByteToHexString(upper) +halfByteToHexString(lower);
        return bstring;
    }
    //takes the 4 bit byte and returns a string based on that byte.
    public static String halfByteToHexString(byte halfByte){
        String halfByteString="";
        switch(halfByte){
            case 0:
                halfByteString = halfByteString + "0";
                break;
            case 1:
                halfByteString = halfByteString + "1";
                break;
            case 2:
                halfByteString = halfByteString + "2";
                break;
            case 3:
                halfByteString = halfByteString + "3";
                break;
            case 4:
                halfByteString = halfByteString + "4";
                break;
            case 5:
                halfByteString = halfByteString + "5";
                break;
            case 6:
                halfByteString = halfByteString + "6";
                break;
            case 7:
                halfByteString = halfByteString + "7";
                break;
            case 8:
                halfByteString = halfByteString + "8";
                break;
            case 9:
                halfByteString = halfByteString + "9";
                break;
            case 10:
                halfByteString = halfByteString + "a";
                break;
            case 11:
                halfByteString = halfByteString + "b";
                break;
            case 12:
                halfByteString = halfByteString + "c";
                break;
            case 13:
                halfByteString = halfByteString + "d";
                break;
            case 14:
                halfByteString = halfByteString + "e";
                break;
            case 15:
                halfByteString = halfByteString + "f";
                break;
                
                
        }
        return halfByteString;
    }    
    
    public static String hexToBinaryString(String s){
        char num;
        int i;
        String binaryMsg ="";
        for(i=0; i<s.length();i++){
            num = s.charAt(i);
            switch(num){
                case '0': 
                        binaryMsg = binaryMsg + "0000";
                        break;
                case '1':
                    binaryMsg = binaryMsg + "0001";
                    break;
                case '2':
                    binaryMsg = binaryMsg + "0010";
                    break;
                case '3':
                    binaryMsg = binaryMsg + "0011";
                    break;
                case '4':
                    binaryMsg = binaryMsg + "0100";
                    break;
                case '5':
                    binaryMsg = binaryMsg + "0101";
                    break;
                case '6':
                    binaryMsg = binaryMsg + "0110";
                    break;
                case '7':
                    binaryMsg = binaryMsg + "0111";
                    break;
                case '8':
                    binaryMsg = binaryMsg + "1000";
                    break;
                case '9':
                    binaryMsg = binaryMsg + "1001";
                    break;
                case 'a' | 'A':
                    binaryMsg = binaryMsg + "1010";
                    break;
                case 'b' |'B':
                    binaryMsg = binaryMsg + "1011";
                    break;
                case 'c' | 'C':
                    binaryMsg = binaryMsg + "1100";
                    break;
                case 'd' | 'D':
                    binaryMsg = binaryMsg + "1101";
                    break;
                case 'e' | 'E':
                    binaryMsg = binaryMsg + "1110";
                    break;
                case 'f' |'F':
                    binaryMsg = binaryMsg + "1111";
                    break;
            }
            
        }
        
        return binaryMsg;
    }
    
    
}





class DesEncrypter {
  Cipher ecipher;

  //Cipher dcipher;
//so need to pass in an 8-byte array
  //key is 56 bits (7 bytes) if the input message is 64 bits.
  DesEncrypter(byte[] key) throws Exception {
    DESKeySpec dks = new DESKeySpec(key);
    SecretKeyFactory skf = SecretKeyFactory.getInstance("DES");
    ecipher = Cipher.getInstance("DES");
    SecretKey desKey = skf.generateSecret(dks);
    //dcipher = Cipher.getInstance("DES");
    ecipher.init(Cipher.ENCRYPT_MODE, desKey);
    //dcipher.init(Cipher.DECRYPT_MODE, key);
  }

  public byte[] encrypt(byte[] msg) throws Exception {
    // Encode the string into bytes using utf-8
    

    //byte[] utf8 = msg.getBytes("UTF8");

    // Encrypt
    byte[] enc = Arrays.copyOfRange(ecipher.doFinal(msg),0,8);
    //enc = BASE64EncoderStream.encode(enc);
    //String bytesAsString = new String(enc,"UTF-8");

    // Encode bytes to base64 to get a string
    return enc;
            //bytesAsString;
            //DatatypeConverter.printHexBinary(enc).substring(0, 16);
    //return new sun.misc.BASE64Encoder().encode(enc);
  }
  
  
}