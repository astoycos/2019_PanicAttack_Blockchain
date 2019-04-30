import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
 
public class teraterm 
{
  public static void main(String[] args) throws Exception
  {
    FileReader fr = new FileReader("teraterm.log");
    BufferedReader br = new BufferedReader(fr);
    int counter = 0;
    while (true) 
    {
      String line = br.readLine();
      if (line == null || line == "" || line.compareTo("***** Booting Zephyr OS zephyr-v1.14.0-117-g83de530d5a36 *****") == 0)
      {
        Thread.sleep(1000);
      } 
      else
      {
        String fileName = "data" + counter + ".txt";
        FileWriter fw = new FileWriter(fileName);
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write(line);
        bw.close();
        System.out.println(line);
        counter++;
      }
    }
  }
}