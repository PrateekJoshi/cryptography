import java.lang.*;
import java.util.*;

public class RandomInsecure{
	public static void main(String args[])
	{	
		/* Cryptographically insecure random no */
		Random secRandom=new Random();
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
		/* Both sequences will be same, NO ENTROPY */
		System.out.println("Same result for same seed => NOT CRYPTOGRAPHYHICALLY SECURE !!!");

	}

}
