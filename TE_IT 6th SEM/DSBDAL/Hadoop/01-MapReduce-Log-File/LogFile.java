package LogFile;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class Logfile
{
	public static class MapperClass extends Mapper<LongWritable, Text, Text, IntWritable>
	{
		public static final SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("yyyy-MM-dd HH:mm:SS");
		public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException
		{
			String line = value.toString();
			String[]parts = line.split(",");
			
			if(parts.length >= 8)
			{
				String user = parts[1];
				String logintime = parts[5];
				String logouttime = parts[7];
				
				try 
				{
					Date LoginTime = DATE_FORMAT.parse(logintime);
					Date LogoutTime = DATE_FORMAT.parse(logouttime);
					
					long sessionDuration = LogoutTime.getTime() - LoginTime.getTime();
					int sessionDurationInMinutes = (int) (sessionDuration / (1000 * 60));
					
					context.write(new Text(user), new IntWritable(sessionDurationInMinutes));
				} 
				catch (ParseException e) 
				{
					e.printStackTrace();
				}
			}
		}
	}
	
	public static class ReducerClass extends Reducer<Text, IntWritable, Text, IntWritable> 
	{
		private IntWritable maxDuration = new IntWritable();
		private Text user = new Text();
		int maxAmongAll = Integer.MIN_VALUE;
		
		public void reduce(Text key, Iterable<IntWritable>values, Context con) throws IOException, InterruptedException
		{
			int max = Integer.MIN_VALUE;
			for(IntWritable value: values)
			{
				int d = value.get();
				if(d > max)
				{
					max = d;
				}
			}
			
			maxDuration.set(max);
			con.write(key, maxDuration);
			if(max > maxAmongAll)
			{
				maxAmongAll = max;
				user.set(key); 
			}
		}
		
		protected void cleanup(Context con) throws IOException, InterruptedException
		{
			con.write(new Text("User With Maximum Logged Time"), null);
			con.write(user , new IntWritable(maxAmongAll));
		}
	}
	
	public static void main(String[] args) throws Exception
	{
		Configuration conf = new Configuration();
		String[] files = new GenericOptionsParser(conf, args).getRemainingArgs();
		Job job = Job.getInstance(conf, "Max Logged IP");
		Path input = new Path(files[0]);
		Path output = new Path(files[1]);
		job.setJarByClass(Logfile.class);
		job.setMapperClass(MapperClass.class);
		job.setReducerClass(ReducerClass.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);
		FileInputFormat.addInputPath(job, input);
		FileOutputFormat.setOutputPath(job, output);
		System.exit(job.waitForCompletion(true)?0:1);
	}
}