/*
 *  Karl Bigley-Bodlak
 *  csc650 project 1
    due 10/19/2015 EXTENDED TO 10/22/15 Extended again to 10/26.
    1.implement CBC, OFB, and CFB for encryption 
the ciphertext block generated from CBC shoud be 64 bits long (8bytes)
    OFB and CFB should ba able to generate any k-bit ciphertext block (1<=k<=64)

    2.Implement CBC residue for integrity protection

    3. implement CBC encryption for both integrity and confidentiality
    use examples to show why this scheme does not work.
    write a brief report in PDF format that includes a description of what you did and
    screenshots of the execution output from each of your programs
 */
package csc650project1;
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
 * @author Karl BIgley-Bodlak
 */
public class Csc650project1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        
        Scanner input = new Scanner(System.in);
        System.out.println("test CBC encoder, please only use hexidecimal values.");
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
        System.out.println(Cbc(m,key,IV));
        //hexStringToByteArray(m);
        //System.out.println("Final output for OFB:  " + OFB(m,key,IV, k));
        //}
    }
    
    
public static String Cbc(String m, String key, String IV) throws Exception{
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
        }
        //System.out.println("after DES on block "+i+ " " +xorElement);
        finalString = finalString +xorElement;
    }
    
    
    /*
    BETTER IDEA: 
    */
    
    /*int messagePieceInt;
    //Storing substrings of the message as integers (16bit).  
    //so each int can only hold 1/2 of a block. (4 characters/bytes)
    while(numIndexes>0){
        messagePiece = m.substring(4*i , (4*i)+4);
        System.out.println(messagePiece);
        messagePieceInt = Integer.parseInt(messagePiece, 16);
        messageInts[i] = messagePieceInt;
        numIndexes = numIndexes-1;
        i= i+1;
    }*/
    /*
        idea of next section:
        the first four iterations will xor the first block with the key.
        then those first four indexes will be combined into a string and sent off to DES.
        once DES is done, the returned string will replace the key for the xor element
        the returned string will be broken up into four substrings and stored as ints again.
        then iterate with the new xor element.
    
    */
    
    
    //the first  loop will xor the first plaintext block with the IV.
    //ater that, it uses the ciphertext from the previous block.
    
    /*for(i=0;i<numBlocks;i++){
        if(i==0){
            //xors each 4 chars of the key with each 4 chars of the first block of the message.
            //then adds the String of the result to the message that will be sent to DES.
            for( j=0; j<2; j++){
                ivPiece = IV.substring(4*j, j+4);
                ivPieceInt = Integer.parseInt(ivPiece, 16);
                messageInts[j] = messageInts[j] ^ ivPieceInt;
                pieceForDES = pieceForDES + Integer.toHexString(messageInts[j]);
            }
            
            
        }else{
            
            for( j=0; j<2; j++){
                ivPiece = xorElement.substring(4*j, j+4);
                ivPieceInt = Integer.parseInt(ivPiece, 16);
                messageInts[2*i+j] = messageInts[2*i+j] ^ ivPieceInt;
                pieceForDES = pieceForDES + Integer.toHexString(messageInts[2*i+j]);
            }
        }
        
        
        MAJOR PROBLEM: what comes out of DES IS NOT A HEX NUMBER.
        
        //xorElement = encrypto.encrypt(pieceForDES);
        for(j=0; j<2; j++){
             ivPiece = xorElement.substring(j, j+4);
             messageInts[2*i+j] = Integer.parseInt(ivPiece,16);
        }        
        
        pieceForDES="";
    }
    */
    //after everything is encrypted, convert all the ints back to strings and 
    //concat them to make the final encrypted message
    
    /*for(i=0;i<k;i++){
        finalString = finalString + Integer.toHexString(messageInts[i]);
    }
    return finalString;*/
    //int origIndex =0;
    
    /*byte[] encodedKey = BASE64.decodeBase64(key);
    //byte[] fullMessage = m.getBytes();  
    //each hex value is a byte, so we just need to split it up by each 8 bytes.
    //length corresponds to the number of bytes that will by used!  two hex chars = 1 byte.
    //Once we get the input, we put it into a 2-d array, each one holding an int that was converted from 32 chars in the string.
    if we get less than 32 chars from the string, stop copying things over.
    */
    
    /*
        Different idea: Convert the string to a binary string.
    
    */
    
    //byte[][] block = new byte[][8];
    
    //int msg = Integer.parseInt(m,16); //now we have the oiginal message as an integer
    
    //System.out.println("Original message  " +msg +"\n binary of message " +Integer.toBinaryString(msg));
    
    //IDEA: convert string to int, xor ints, then convert to string again.
    //repeat by taking this final string and convert to int with next block. Then convert again.
    
    //int byteIV = Integer.parseInt(IV, 16); //the IV as an int
    
    //byte[] byteIV = IV.getBytes();
    
    //System.out.println("Original IV  " +byteIV + "\n orignal IV binary " + Integer.toBinaryString(byteIV));
    //int xor = msg ^ byteIV; //the initial xor with the IV and first block of the plaintext.
    //System.out.println("xor the IV with first block." + xor + "\n xored binary " + Integer.toBinaryString(xor));
    //byte[] xorArray = new byte[8];
    /*do{
        for(byte b : fullMessage)
            xorArray[i] = b ^ byteIV[i++]; 
    }while
    System.out.*/
    //copyOfRange();
    //DesEncrypter crypto = new DesEncrypter(key);
            //IV.getBytes();
    //byte[] ciphertext = message XOR byteIV;
    
    
    //loop of encryption begins
    //while(is64 = true){
        
    //
    
    
    
    //return em;
        System.out.print("final result: ");
        return finalString;
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


    static String hexToBin(String hex){
          return new BigInteger(hex,16).toString(2);
    }
    
    static String cbcWithBits(String m, String key, String IV){
        String em="";
        
        return em;
    }
    /*
    a little different. check the slides for more info.
    */
    /*public static String OFB(String m, String key, String IV, int k) throws Exception{
        String finalMessage="";
        int numToPad;
        int i=0;
        String padding = "0";
        String messagePiece;
        String ivPiece;
        int ivPieceInt;
        boolean is16Key=true;
        boolean is16Msg = true;
        
        byte[] bytePadding;
        //key length check; pads it out with zeroes if its not long enough.
        if (key.length()<8){
            numToPad = 8-key.length(); 
            while(is16Key){
                key = padding + key;
                numToPad = numToPad - 1;
                if(numToPad<=0){
                    is16Key = false;
                }
            }
        }
        
        
        is16Key=true;
        byte[] keyDES = key.getBytes();
        DesEncrypter encrypto = new DesEncrypter(keyDES);
        
        byte[] ivBytes = IV.getBytes();
        if(ivBytes.length<k){
            numToPad = k-ivBytes.length%k; 
            bytePadding = new byte[numToPad];
            ivBytes = concat(ivBytes, bytePadding);   //so that when we get the first k bits, they won't be zeroes.
        
        }
         

        //END PADDING BEGIN LOGIC.
        byte[] msgBytes = m.getBytes();
        byte[] finalBytes;
        int paddingLength;
        int j;
        int a;
        
        //if the message is not a multiple of k.
        /*if(msgBytes.length%k !=0){
            paddingLength = k - msgBytes.length%k;
            bytePadding = new byte[paddingLength];
            msgBytes = concat(bytePadding,msgBytes);
        }
        
        int numBlocks = msgBytes.length/k;
        //IV gets encrypted with DES.
        
        /*
            PROBLEM, k REFERS TO BITS, NOT BYTES. BYTES ARE 8 BITS.
            HAVE TO CONVERT TO BINARY STRING AND RUN XOR WITH ENCRYPTED IV THAT WAY.
            THEN YOU GET XORED STRING TO ADD TO FINAL STRING.
        
        
        
        byte[] cipherBlock;
        for(i=0;i<numBlocks;i++){
            a=0;
            //if(i==0){  //first iteration we don't have shift
                cipherBlock = encrypto.encrypt(ivBytes).getBytes();
                ivBytes = Arrays.copyOfRange(ivBytes, k, ivBytes.length);
                //xor on the plainbytes and the 
                for(j=i*k; j<i*k+k;j++){
                    msgBytes[j] = (byte) (msgBytes[j] ^ cipherBlock[a]);
                    a++;
                }
            //}
            //shifting IV and concatenating the cipherblock to it.
            ivBytes = concat(ivBytes, Arrays.copyOfRange(cipherBlock, 0, k));
        }
        */
        
        //return finalMessage;
    //}

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
        byte insert;
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
/*
sooooo: I need to send a 64 bit string? no.
so i need to pass in an array of bytes length 64 for the key.
*/

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
    byte[] enc = Arrays.copyOfRange(ecipher.doFinal(msg),0,8);
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

//one-line hex-to-binary code: new BigInteger(hex,16).toString(2);

/*
    encrypting the IV and then xoring that with the plaintext to encrypt the message.
    the IV gets shifted k bits
*/

/*
alternative: strings and chars.
4 chars to a block in java
pad out the message and check the key.
break up the string into substrings of 4 chars each.
for the key, it has to be 4 chars long.
the IV also has to be 4 chars long.
turn the substring into a byte array


so if I run it on each index entry, it could convert those 4 characters into a 
byte array of length 8, which can then be sent to DES.
once it returns the string, i can then convert it to an int again.
but how to get the 7 byte key?
*/

/*
    ok, so we need a key of at least length 8, implying each char is indeed a byte.


*/