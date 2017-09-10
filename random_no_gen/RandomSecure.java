import java.lang.*;
import java.security.SecureRandom;

public class RandomSecure{
	public static void main(String args[])
	{	
		/* Cryptographically secure random no */
		SecureRandom secRandom=new SecureRandom();
		/* Set seed */
		secRandom.setSeed(100);
		/* Now generate 10 random nos for 1st sequence */
		System.out.println("Random nos in first sequence for seed(100) : ");
		for(int i=0;i<10;i++)
			System.out.println(secRandom.nextInt());
		/*set the same seed again */
		secRandom.setSeed(100);
		/* Now generate 10 random nos for 2nd sequence */
		System.out.println("Random nos in second sequence for seed(100) : ");
	        for(int i=0;i<10;i++)
			System.out.println(secRandom.nextInt());
		/* Both sequences will be not be same, ENTROPY will be applied by java */
		System.out.println("Different result for same seed => CRYPTOGRAPHYHICALLY SECURE :) ");

	}

}
