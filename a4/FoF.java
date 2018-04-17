import java.io.IOException;
import java.util.StringTokenizer;
import java.util.Arrays;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class FoF {

  public static class TokenizerMapper
       extends Mapper<Object, Text, Text, IntWritable>{

    private final static IntWritable one = new IntWritable(1);
    private Text word = new Text();

    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {

      // StringTokenizer itr = new StringTokenizer(value.toString());
      // while (itr.hasMoreTokens()) {
      //   word.set(itr.nextToken());
      //   one.set(3);
      //   context.write(word, one);
      // }
      String[] data = value.toString().split(" ");
      String head = data[0];
      for (int i = 1; i < data.length; i++) {
          for (int j = i + 1; j < data.length; j++) {
              int[] nums = {Integer.parseInt(data[0]), Integer.parseInt(data[i]), Integer.parseInt(data[j])};
              Arrays.sort(nums);
              String[] outputs = {
                  nums[2] + " " + nums[0] + " " + nums[1],
                  nums[0] + " " + nums[1] + " " + nums[2],
                  nums[1] + " " + nums[0] + " " + nums[2]
              };
              for (int iter = 0; iter < outputs.length; iter++) {
                  word.set(outputs[iter]);
                  one.set(1);
                  context.write(word, one);
              }
          }
      }
    }
  }

  public static class IntSumReducer
       extends Reducer<Text,IntWritable,Text,NullWritable> {
    private IntWritable result = new IntWritable();
    public void reduce(Text key, Iterable<IntWritable> values,
                       Context context
                       ) throws IOException, InterruptedException {
      int count = 0;
      for (IntWritable i : values) {
          if (count == 2) {
              context.write(key, NullWritable.get());
          }
          count++;
      }
    }
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "word count");
    job.setJarByClass(FoF.class);
    job.setMapperClass(TokenizerMapper.class);
    //job.setCombinerClass(IntSumReducer.class);
    job.setReducerClass(IntSumReducer.class);
    job.setMapOutputKeyClass(Text.class);
    job.setMapOutputValueClass(IntWritable.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(NullWritable.class);
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
