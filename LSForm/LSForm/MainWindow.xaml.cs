using System;
using System.Globalization;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml;

namespace LSForm
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            CultureInfo.CurrentCulture = CultureInfo.InvariantCulture;
            InitializeComponent();
        }

        public float Width0 { get; set; }
        public float Width1 { get; set; }
        public int Iters { get; set; }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            Grid grid = new Grid();
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(24.0) });
            grid.ColumnDefinitions.Add(new ColumnDefinition());
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(24.0) });
            grid.Margin = new Thickness(0.0, 0.0, 0.0, 8.0);
            TextBox boxR = new TextBox();
            boxR.Text = "R";
            Grid.SetColumn(boxR, 0);
            TextBox boxE = new TextBox();
            boxE.Margin = new Thickness(8.0, 0.0, 8.0, 0.0);
            boxE.Text = $"Rule #{StackRules.Children.Count}";
            Grid.SetColumn(boxE, 1);
            Button button = new Button();
            button.Content = "-";
            button.Click += ButtonRemove_Click;
            Grid.SetColumn(button, 2);
            grid.Children.Add(boxR);
            grid.Children.Add(boxE);
            grid.Children.Add(button);
            StackRules.Children.Insert(StackRules.Children.Count - 1, grid);
        }

        private void ButtonRemove_Click(object sender, RoutedEventArgs e)
        {
            if (StackRules.Children.Count > 2)
                StackRules.Children.Remove((sender as Button).Parent as Grid);
        }

        private void BoxIter_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                string input = BoxIter.Text;
                Iters = int.Parse(input);
                if (Iters < 0)
                    throw new Exception();
                BoxIter.Background = new SolidColorBrush(Colors.White);
            }
            catch
            {
                BoxIter.Background = new SolidColorBrush(Colors.Pink);
            }
        }

        private void BoxWidth0_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                string input = BoxWidth0.Text;
                Width0 = float.Parse(input);
                if (Width0 < 0.0)
                    throw new Exception();
                BoxWidth0.Background = new SolidColorBrush(Colors.White);
            }
            catch
            {
                BoxWidth0.Background = new SolidColorBrush(Colors.Pink);
            }
        }

        private void BoxWidth1_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                string input = BoxWidth1.Text;
                Width1 = float.Parse(input);
                if (Width1 < 0.0)
                    throw new Exception();
                BoxWidth1.Background = new SolidColorBrush(Colors.White);
            }
            catch
            {
                BoxWidth1.Background = new SolidColorBrush(Colors.Pink);
            }
        }
    }
}
