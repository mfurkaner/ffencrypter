using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zEntryptUI
{
    internal class ServiceHandler
    {
        private static ServiceHandler? _instance = null;
        private ServiceHandler()
        {
        }
        public static ServiceHandler GetInstance()
        {
            if (_instance == null)
            {
                _instance = new ServiceHandler();
            }
            return _instance;
        }

        public const string servicePath = "resources\\zEncrypter.exe";
        public string configPath = "config.in";

        public string StartEngine(string configpath = "")
        {
            if (configpath == string.Empty)
                configpath = configPath;
            Process process = new Process();
            // Configure the process using the StartInfo properties.
            process.StartInfo.FileName = servicePath;
            process.StartInfo.ArgumentList.Add("-c");
            process.StartInfo.ArgumentList.Add(configpath);
            process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            process.StartInfo.CreateNoWindow = true; // Prevent creating a new window

            // Redirect standard output and error
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.RedirectStandardError = true;
            process.StartInfo.UseShellExecute = false; // Required for redirection

            // Start the process
            process.Start();

            // Read the output streams
            string standardOutput = process.StandardOutput.ReadToEnd();
            string errorOutput = process.StandardError.ReadToEnd();

            process.WaitForExit();

            return standardOutput;
        }
    }
}
