package bgu.spl.net.api;


import bgu.spl.net.api.Users.User;

import java.util.*;

public class Course {
    private int courseNum;
    private String courseName;
    private List<Integer> KdamCoursesList;
    private int numOfMaxStudents;
    private List<User> RegisterStudents;

    public Course(int courseNum, String courseName,
                  List<Integer> KdamCoursesList, int numOfMaxStudents){
        this.courseNum = courseNum;
        this.courseName = courseName;
        this.KdamCoursesList = KdamCoursesList;
        this.numOfMaxStudents = numOfMaxStudents;
        this.RegisterStudents = new ArrayList<>();
    }

    public int getCourseNum() {
        return courseNum;
    }

    public int getNumOfMaxStudents() {
        return numOfMaxStudents;
    }

    public List<Integer> getKdamCoursesList() {
        return KdamCoursesList;
    }

    public String getCourseName() {
        return courseName;
    }

    public synchronized boolean RegisterStudent(User user){
        boolean kdam_courses = true;
        for (Course course : user.getCourses()){
            if (!KdamCoursesList.contains(course.courseNum)) {
                kdam_courses = false;
            }
        }
        if(RegisterStudents.size() < numOfMaxStudents && kdam_courses) {
            RegisterStudents.add(user);
            return true;
        }
        return false;
    }

    public int RegisteredNum(){
        return RegisterStudents.size();
    }

    @Override
    public String toString() {
        String output = "Course: (" + courseNum + ") " + courseName +"\n";
        output += "Seats Available: " + RegisterStudents.size() + " / " + numOfMaxStudents +"\n";
        List<String> names = new ArrayList<>();
        for (User user : RegisterStudents) {
            names.add(user.getUsername());
        }
        Collections.sort(names);
        output += "Students Registered: " + names.toString();
        return output;
    }
}
