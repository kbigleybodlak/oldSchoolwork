/*
 *  Karl Bigley-Bodlak
 *  csc650 project 1
    due 10/19/2015 EXTENDED TO 10/26/15
    1.implement CBC, OFB, and CFB for encryption 
the ciphertext block generated from CBC shoud be 64 bits long (8bytes)
    OFB and CFB should ba able to generate any k-bit ciphertext block (1<=k<=64)

    2.Implement CBC residue for integrity protection

    3. implement CBC encryption for both integrity and confidentiality
    use examples to show why this scheme does not work.
    write a brief report in PDF format that includes a description of what you did and
    screenshots of the execution output from each of your programs
 */
package csc650projectcbcre;
import javax.crypto.Cipher;
//import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.util.Scanner;

import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;
//import sun.misc.BASE64Decoder;
//import sun.misc.BASE64Encoder;
import java.util.Arrays;
//import javax.xml.bind.DatatypeConverter;
import java.math.BigInteger;


/**
 * 
 * @author Karl Bigley-Bodlak
 */
public class Csc650projectCBCRe {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        
        Scanner input = new Scanner(System.in);
        System.out.println("test CBC encoder with CBC residue for integrity, please only use hexidecimal values. Will only return cbc residue.");
        System.out.println("please type message to be encrypted.");
        String m = input.nextLine();
        System.out.println("Please type key of length 16 or longer to use for DES encryption. otherwise the string is padded with zeroes");
        String key = input.nextLine();
        System.out.println("Please type the initial vector as a String.");
        String IV = input.nextLine();
        /*System.out.println("Please enter the k for OFB and CFB.");
        int k = input.nextInt();
        if(k>64 || k<1){
            System.out.println("Error: k needs to be 1<=k<=64");
          
        }else{*/
        System.out.println(CbcRe(m,key,IV));
        //hexStringToByteArray(m);
        //System.out.println("Final output for OFB:  " + OFB(m,key,IV, k));
        //}
    }
    
    //Should only return the cbc residue.
public static String CbcRe(String m, String key, String IV) throws Exception{
    String em = "";
    int i=0;
    int j = 0;
    int k =0;
    //the array that will hold the integers of the message
    int[] messageInts;
    String padding = "0";
    boolean is16Key = true;
    boolean is16Msg = true;
    String xorElement="";
    String pieceForDES="";
    String finalString="";
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
    is16Key=true;
    byte[] keyDES = hexStringToByteArray(key);
    DesEncrypter encrypto = new DesEncrypter(keyDES);
    //padding the IV if its under 16 chars.
    if(IV.length()<16){
        numToPad = 16-IV.length(); // so if key length is 14, numtopad is 2
        while(is16Key){
            IV = padding + IV;
            numToPad = numToPad - 1;
            if(numToPad<=0){
                is16Key = false;
            }
        }
        System.out.println("IV padded to: "+IV);
    }
    
    int blokRemainder = m.length()%16;
    //System.out.println(blokRemainder);

    //When the message ist  amultiple of 16 in length, pad it out.
    if((m.length()%16 >0)){
        numToPad = 16-blokRemainder;
        while(is16Msg){
            m = padding +m;
            numToPad = numToPad -1;
            if(numToPad<=0){
                is16Msg = false;
            }
        }
        System.out.println("padded message:  " +m);
    }
    //finding out how many blocks will need to be encrypted.  We Know the last block is full after padding it.
    int numBlocks = m.length()/16;
    //messageInts = new int[(2*numBlocks)];
    //int numIndexes = 2*numBlocks;
    //k= numIndexes;
    String cbcResidue ="";
    for(i=0;i<numBlocks;i++){
        
        messagePiece = m.substring(16*i, 16*i+16);
        messageBytes = hexStringToByteArray(messagePiece);
        //System.out.println("messageBYtes before xor  " + messageBytes[7]);
        if(i==0){
            ivPiece = IV.substring(0, 16);
            ivBytes = hexStringToByteArray(ivPiece);
        }else{
            ivPiece = xorElement;
            ivBytes = hexStringToByteArray(ivPiece);
        }
        messageBytes = xorBytes(messageBytes, ivBytes);
        //System.out.println("messageBytes after xor:  " +messageBytes[7]);
        messageBytes = encrypto.encrypt(messageBytes);
        xorElement = "";
        for(j=0;j<8;j++){
            
            xorElement = xorElement + byteToHexString(messageBytes[j]);
            if(i==numBlocks-1){
                cbcResidue = cbcResidue + byteToHexString(messageBytes[j]);
            }
        
        }
        //System.out.println("after DES on block "+i+ " " +xorElement);
        finalString = finalString +xorElement;
    }
    
    //System.out.println("cbc Residue: "+cbcResidue);
    System.out.print("cbc residue final result: ");
    return cbcResidue;
    }
        
    public static byte[] xorBytes(byte[] plaintext, byte[]ciphertext){
        int i;
        if (ciphertext.length==0){
            //System.out.println("ERROR: 2nd arg in xorbytes doesnt exist.");
        }
        if (plaintext.length==0){
            //System.out.println("ERROR: 1st arg in xorbytes doesnt exist.");
        }
        for(i=0;i<plaintext.length;i++){
            plaintext[i] = (byte) (plaintext[i] ^ ciphertext[i]);
        }
        return plaintext;
    }


   public static byte[] concat(byte[] a, byte[] b) {
    int aLen = a.length;
    int bLen = b.length;
    byte[] c= new byte[aLen+bLen];
    System.arraycopy(a, 0, c, 0, aLen);
    System.arraycopy(b, 0, c, aLen, bLen);
    return c;
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
    //converts a string of hex characters to a byte array.
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
            insert=0;
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
      int i;
    // Encrypt
    byte[] enc = Arrays.copyOfRange(ecipher.doFinal(msg),0,16);
    //for(i=0; i<8;i++)
      //  System.out.println("right after DES :  " + enc[i]);
    //enc = BASE64EncoderStream.encode(enc);
    //String bytesAsString = new String(enc,"UTF-8");

    // Encode bytes to base64 to get a string
    return enc;
            //bytesAsString;
            //DatatypeConverter.printHexBinary(enc).substring(0, 16);
    //return new sun.misc.BASE64Encoder().encode(enc);
  }
  
  
}


